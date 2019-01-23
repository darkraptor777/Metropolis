#include "pch.h"
#include "Board.h"


Board::Board(SDL_Renderer* renderer, int pixelBoardSize, AH_Cursor* cursor)
{
	SDL_Log("default board constructor called.");
	Select = Mix_LoadWAV("Assets/Sound/SFX/Select.wav");
	Shoot = Mix_LoadWAV("Assets/Sound/SFX/Shoot.wav");
	Mix_VolumeChunk(Select, 100);
	Mix_VolumeChunk(Shoot, 100);

	srand(time(NULL));
	this->cursor = cursor;
	this->renderer = renderer;
	int r;
	hoverSprite = new AH_Sprite(renderer, ((int)(this->cursor->getX()/ dim))*20, ((int)(this->cursor->getY()/ dim))*20, 20, 20, 1, 1, (int)(pixelBoardSize / dim));
	hoverSprite->load("Assets/Sprites/Hover.png");
	
	this->pixelBoardSize = pixelBoardSize;

	int gridSize = sizeof(grid) / sizeof(Entity*);

	for (int x=0; x < gridSize; x++)
	{
		if (x > 900)
			SDL_Log("test");

		r = rand() % 13;
		
		if (r <= 9)
			grid[x] = new Floor(renderer, (int)(x%dim), (int)(x / dim), (int)(pixelBoardSize / dim));
		else if (r <= 10 && r > 9)
			grid[x] = new Wall(renderer, (int)(x%dim), (int)(x / dim), (int)(pixelBoardSize / dim));
		else if (r > 10 && r <= 12)
			grid[x] = new Wallsmall(renderer, (int)(x%dim), (int)(x / dim), (int)(pixelBoardSize / dim));
		else
			SDL_Log("%i", r);
	}
	grid[player] = new Character(renderer, 0, 0, 8, 8, (string)"Player", false, true, true, true, "Assets/Sprites/Player.png", 20, 20, 1, 1, (pixelBoardSize / dim), true, true, 5);
	
	int rX = rand() % (dim-1);
	int rY = rand() % (dim - 1);
	enemy = (rY*dim) + rX;
	grid[enemy] = new Character(renderer, rX, rY, 8, 8, (string)"Enemy", false, true, true, true, "Assets/Sprites/Enemy.png", 20, 20, 1, 1, (pixelBoardSize / dim), true, true, 5);
	grid[enemy]->setX(rX);
	grid[enemy]->setY(rY);
}


Board::~Board()
{
	SDL_Log("default board destructor called.");
	delete cursor;
	delete hoverSprite;
	Mix_FreeChunk(Select);
	Mix_FreeChunk(Shoot);
	//delete player;
	/*for (int x = 0; x < sizeof(grid);x++)
	{
		delete grid[x];
	}*/
}

void Board::render()
{
	int gridSize = sizeof(grid) / sizeof(Entity*);
	for (int x = 0; x < gridSize; x++)
	{
		grid[x]->render();
	}
	hoverSprite->render();
}

SDL_Event Board::currentEvent;

void Board::handleEvents()
{
	SDL_Log("#######################NOW HANDLING INPUT##########################");
	SDL_PollEvent(&currentEvent);
	if((currentEvent.type==SDL_MOUSEBUTTONDOWN)||(currentEvent.type=SDL_KEYDOWN) && currentEvent.key.repeat == NULL)
	{ 
		int cX = ((cursor->getX() + 1) / (int)(pixelBoardSize / dim));
		int cY = ((cursor->getY() + 1) / (int)(pixelBoardSize / dim));
		int cI = (cY*dim) + cX;
		//turns out, shockingly, inverting it breaks a lot of stuff
		//X and Y have to be backwards here for some reason, despite it beign fine everywhere else *shrug*
		SDL_Log("Mouse click at x: %i y: %i (actual index: %i)", cX, cY, cI);
		int pI = (grid[player]->getY()*dim) + grid[player]->getX();


		if(currentEvent.button.button == SDL_BUTTON_LEFT||currentEvent.key.keysym.sym == SDLK_RETURN)
		{
			SDL_Log("Move Button Pressed");
			if (playerTurn)
				tryMove(pI, cI);
			else
				SDL_Log("It is not your turn >:I");
		}
		if (currentEvent.button.button == SDL_BUTTON_RIGHT || currentEvent.key.keysym.sym == SDLK_SPACE)
		{
			SDL_Log("Shoot Button Pressed");
			if (playerTurn)
				tryShoot(pI, cI);
			else
				SDL_Log("It is not your turn >:I");
		}
	}
	
}


void Board::update()
{
	SDL_Log("Updating Board");
	
	SDL_Log("Updating HoverSprite");
	int cX = ((int)((cursor->getX() + 1) / (int)(pixelBoardSize / dim)));
	int cY = ((int)((cursor->getY() + 1) / (int)(pixelBoardSize / dim)));
	hoverSprite->setX(cX*20);
	hoverSprite->setY(cY*20);
	int actions = (dynamic_cast<Character*>(grid[player]))->getActions();
	

	//only do these checks if cursor is on the board
	if (pixelBoardSize > cursor->getX())
	{
		
		if(playerTurn && grid[(cY*dim) + cX]->getName()=="Enemy" && hoverSprite->getPath() != "Assets/Sprites/Hover_Enemy.png")
			hoverSprite->load("Assets/Sprites/Hover_Enemy.png");
		else if (playerTurn && grid[(cY*dim) + cX]->getName() != "Enemy")
		{
			if (!grid[(cY*dim) + cX]->isPathable() || (getDistance(player, (cY*dim) + cX) > (dynamic_cast<Character*>(grid[player]))->getMaxMovement()*actions && hoverSprite->getPath() != "Assets/Sprites/Hover_X.png"))
				hoverSprite->load("Assets/Sprites/Hover_X.png");
			else if (getDistance(player, (cY*dim) + cX) > (dynamic_cast<Character*>(grid[player]))->getMaxMovement()*(actions == 0 ? actions : actions - 1) && getDistance(player, (cY*dim) + cX) <= (dynamic_cast<Character*>(grid[player]))->getMaxMovement()*actions && hoverSprite->getPath() != "Assets/Sprites/Hover_Sprint.png")
				hoverSprite->load("Assets/Sprites/Hover_Sprint.png");
			else if (getDistance(player, (cY*dim) + cX) <= (dynamic_cast<Character*>(grid[player]))->getMaxMovement()*(actions == 0 ? actions : actions - 1) && hoverSprite->getPath() != "Assets/Sprites/Hover.png")
				hoverSprite->load("Assets/Sprites/Hover.png");
		}

		if (!playerTurn && hoverSprite->getPath() != "Assets/Sprites/Hover_X.png")
			hoverSprite->load("Assets/Sprites/Hover_X.png");
	}
	else
	{
		if(hoverSprite->getPath() != "Assets/Sprites/Hover_Clear.png")
			hoverSprite->load("Assets/Sprites/Hover_Clear.png");
	}
	
}

void Board::toggleTurn()
{
	if (playerTurn)
	{
		SDL_Log("It is now the Enemys Turn");
		playerTurn = false;
		dynamic_cast<Character*>(grid[enemy])->refreshActions();
		aiConsiderMove();
		tryShoot(enemy, player);
	}
	else
	{
		SDL_Log("It is now the Players Turn");
		playerTurn = true;
		dynamic_cast<Character*>(grid[player])->refreshActions();
	}
}

void Board::aiConsiderMove()
{
	SDL_Log("AI Considering Move");
	int enemyX = dynamic_cast<Character*>(grid[enemy])->getX();
	int enemyY = dynamic_cast<Character*>(grid[enemy])->getY();

	int targetX, targetY;

	bool tryingToMove = true;
	while (tryingToMove)
	{
		dynamic_cast<Character*>(grid[enemy])->Move(targetX,targetY);
		if (((enemyY + targetY)*dim) + (targetX + enemyX) <= dim * dim && (targetX + enemyX)<dim && (enemyY + targetY)<dim)
		{
			SDL_Log("Attempting to move to x: %i y: %i", (targetX + enemyX), (enemyY + targetY));
			bool attemptSuccess = tryMove((enemyY*dim) + enemyX, ((enemyY + targetY)*dim) + (targetX + enemyX));
			if (attemptSuccess)
				tryingToMove = false;
		}
	}
}

bool Board::tryShoot(int a, int b)
{
	SDL_Log("Attempting to Shoot");
	SDL_Log("a!=b %i", a != b);
	if (pixelBoardSize > cursor->getX() && (a != b)&&(b==player||b==enemy)&& dynamic_cast<Character*>(grid[a])->getActions()>0)
	{
		Mix_PlayChannel(-1, Shoot, 0);
		int left,right,above,below;
		left = b - 1;
		right = b + 1;
		above = b - dim;
		below = b + dim;
		//checks for board edges
		if (b%dim == 0||left<0||grid[left]->getName()==(string)"Floor")
			left = NULL;
		if ((b + 1) % dim == 0 || right>(dim*dim) || grid[right]->getName() == (string)"Floor")
			right = NULL;
		if (above < 0 || grid[above]->getName() == (string)"Floor")
			above = NULL;
		if (below > (dim*dim) || grid[below]->getName() == (string)"Floor")
			below = NULL;
		//
		int neighbours[4] = { left,right,above,below };
		float cover=0;
		for (int i = 0; i < 4; i++)
		{
			if (neighbours[i] != NULL)
			{
				float percent = dynamic_cast<Cover*>(grid[neighbours[i]])->getPercent();
				if (percent > cover)
					cover = percent;
			}
		}
		bool hit;
		int hitChance = rand() % 100;
		SDL_Log("hitChance: %i  cover: %i", hitChance, (int)(cover * 100)+10);
		if (hitChance > (int)(cover * 100)+10)
		{
			hit = true;
			SDL_Log("HIT!");
			if (playerTurn) //if it's the player shooting
				score += 20;
			else //if it's the enemy shooting
				score -= 10;
		}
		else
		{
			hit = false;
			SDL_Log("MISS!");
		}
		if (hit)
		{
			grid[b]->TakeDamage(dynamic_cast<Character*>(grid[a])->getDamage());
		}
		dynamic_cast<Character*>(grid[a])->useActions(2);
	}
	else
	{
		SDL_Log("Cannot Shoot Target");
		return false;
	}
}

bool Board::tryMove(int a, int b)
{
	SDL_Log("a!=b %i", a != b);
	//SDL_Log("checkMove(a,b) %i", checkMove(a, b));
	if (( (playerTurn&&pixelBoardSize > cursor->getX())|| !playerTurn )&&checkMove(a,b)&&(a!=b))
	{
		Mix_PlayChannel(-1, Select, 0);
		SDL_Log("Valid Move");
		moveEntity(renderer, a, b);
		return true;
	}
	else
	{
		SDL_Log("Invalid Move");
		return false;
	}
}

bool Board::checkMove(int a, int b)
{
	if (b > (dim*dim))
		return false;

	//SDL_Log("sanity %i", false);
	//SDL_Log("isPathable() %i", grid[b]->isPathable());
	int movement = (dynamic_cast<Character*>(grid[a]))->getMaxMovement();
	int actions  = (dynamic_cast<Character*>(grid[a]))->getActions();
	int distance = getDistance(a, b);

	//SDL_Log("movement: %i actions: %i distance: %i", movement, actions, distance);

	//SDL_Log("sprint: %i", (movement * 2 <= distance && actions >= 2));
	//SDL_Log("walk: %i", (movement <= distance && actions >= 1));

	if (!grid[b]->isPathable())
		SDL_Log("Movement would result in collision");

	if (grid[b]->isPathable() && ((movement*2 >= distance && actions >= 2 ) || (movement >= distance && actions >= 1)))
	{
		if (canReachFrom(a, b, (movement*2)))
			return true;
		else
			return false;
	}
	else
		return false;
}

bool Board::canReachFrom(int a, int b, int range)
{
	int distance;
	
	distance = getDistance(a, b);
	//SDL_Log("%i",distance);
	if (range >= distance)
	{
		SDL_Log("Target Movement Within Range");
		return true;
	}
	else
	{
		SDL_Log("Target Movement Outside Range");
		return false;
	}
	//to make advanced use Dijkstra or A* pathfinding (will require creating a node class and tree class ;-;)
}

void Board::moveEntity(SDL_Renderer* renderer, int a, int b)
{
	

	SDL_Log("Moving Entity from %i to %i", a, b);
	delete grid[b];
	grid[b] = grid[a]->clone();
	//SDL_Log("%s", grid[b]->getName().c_str());
	//SDL_Log("%s",grid[a]->getName().c_str());
	grid[a] = new Floor(renderer,a%dim,(int)(a/dim),(int)(pixelBoardSize/dim));
	//SDL_Log("%s", grid[a]->getName().c_str());
	grid[b]->setX(b%dim);
	grid[b]->setY((int)(b / dim));
	grid[b]->getSprite()->reload();
	if (playerTurn)
		player = b;
	else
		enemy = b;

	//sprinting requires two actions
	if (getDistance(a, b) > (dynamic_cast<Character*>(grid[b]))->getMaxMovement())
		(dynamic_cast<Character*>(grid[b]))->useActions(2);
	else
		(dynamic_cast<Character*>(grid[b]))->useActions(1);
	//SDL_Log("raw    x: %i y: %i", (b%dim), ((int)b/dim));
	//SDL_Log("get    x: %i y: %i", grid[b]->getX(), grid[b]->getY());
	//SDL_Log("raw    b: %i ", b); 
}

int Board::getDistance(int a, int b)
{
	int aX, aY, bX, bY, distance;
	aX = a % dim;
	aY = a / dim;
	bX = b % dim;
	bY = b / dim;
	distance = pow((pow((bY - aY), 2) + pow((bX - aX), 2)), 0.5); //pythagoras
	//SDL_Log("a: %i b: %i", a, b);
	//SDL_Log("((%i - %i)^2 + (%i - %i)^2)^0.5=%i", bY, aY, bX, aX, distance);
	return distance;
}

//raycast broke at the last minute ;-;
bool Board::raycast(int sPoint, int ePoint, int &hitOne, int &hitTwo)
{
	// c Prefix denotes collison point
	// s Prefix denotes start point
	// e Prefix denotes end point
	int sX = sPoint % dim;
	int sY = sPoint/ dim;
	int eX = ePoint % dim;
	int eY = ePoint/ dim;
	//can't divide by 0
	if (eX - sX == 0)
	{
		int greater, lower;
		if (eY < sY)
		{
			greater = sY;
			lower = eY;
		}
		else
		{
			greater = eY;
			lower = sY;
		}
		for (int i = lower; i <= greater; i++)
		{
			if (!grid[(i*dim) + eX]->isPathable())
			{
				return ((i*dim) + eX);
			}
		}
	}
	else
	{
		double m = (eY - sY) / (eX - sX);
		double c = sY - (m*sX);

		SDL_Log("Casting ray from (%s,%s) to (%s,%s)", sX, sY, eX, eY);

		for (int i = 0; i < sizeof(grid); i++)
		{
			int iX = i % dim;
			int iY = i / dim;


			//collisons detection 

			if (iX > sX && iX<eX && iY>sY && iY < eY) //reduces redundant checks
			{
				if (iX == 0)
				{
					double cX = (iY - 0.5 - c) / m;
					if (cX<(iX + 0.5) && cX>(iX - 0.5) && !grid[i]->isPathable()) //can't hit pathable objects
					{
						hitOne = i;
						return true;
					}
				}

				if (iY == 0)
				{
					double cY = (m*(iX - 0.5)) + c;
					if (cY<(iY + 0.5) && cY>(iY - 0.5) && !grid[i]->isPathable())
					{
						hitOne = i;
						return true;
					}
				}

				double cX = (iY + 0.5 - c) / m;
				if (cX<(iX + 0.5) && cX>(iX - 0.5))
				{
					if (sX < eX)
						hitOne = i;
					else if (sX > eX)
						hitOne = i + 1;
					else if (sX = eX)
					{
						hitOne = i;
						hitTwo = i + 1;
					}
					return true;
				}

				double cY = (m*(iX + 0.5)) + c;
				if (cY<(iY + 0.5) && cY>(iY - 0.5))
				{
					hitOne = i;
					hitTwo = i + dim;
					return true;
				}
			}


			//will detect collisions between plane and diamond
			/*
			double cX = (iY - c) / m;
			if (cX<(iX + 0.5) && cX>(iX - 0.5))
			{
				hit = grid[i];
				return true;
			}

			double cY = (m*iX)+c;
			if (cY<(iY + 0.5) && cY>(iY - 0.5))
			{
				hit = grid[i];
				return true;
			}
			*/
		}
		return false;
	}
	
}