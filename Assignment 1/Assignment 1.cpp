// Assignment 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sstream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

//#include "ScreenText.h"

#include "Entity.h"
#include "Timer.h"
#include "Board.h"

#include"AH_Sprite.h"
#include"AH_Cursor.h"
#include "AH_Lumberjack.h"
#include "AH_Text.h"

void handleMenuEvents(AH_Cursor* cursor, bool &InMainMenu, bool &InGame, bool &Running, Mix_Chunk* Select);

using namespace std;

static SDL_Event MenuEvent;

int main(int argc, char* argv[])
{
	Lumberjack* mainLog = new Lumberjack("Logging/Main.log");
	bool InMainMenu = true;
	bool InGame = false;
	bool Running = true;
	const int DELTA_TIME = 100 / 30; //Frame Rate
	Timer FrameTimer;
	Timer GameTimer;
	Timer TurnTimer;
	Timer GameEndTimer;

	stringstream GameTimerSTR, TurnTimerSTR, ScoreSTR, PlayerHPSTR, EnemyHPSTR;
	
	Mix_Music *BGM_game = nullptr;
	Mix_Music *BGM_menu = nullptr;
	Mix_Chunk* Select = nullptr;

	SDL_Log("Hello World!");
	srand(time(NULL));
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL failed to initialise.\n";
		return 1;
	}

	else //if SDL inits fine int sdl_img
	{
		if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
		{
			cout << "SDL_Image failed to initialise.\n";
			SDL_Quit();
			return 1;
		}

		else
		{
			if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
			{
				printf("Warning: Audio has not been found! \n");
				SDL_Quit();
				IMG_Quit();
				return 1;
			}
			else
			{
				TTF_Init();


				BGM_game = Mix_LoadMUS("Assets/Sound/BGM/Hardlight.wav");
				BGM_menu = Mix_LoadMUS("Assets/Sound/BGM/Metropolis.wav");
				Select = Mix_LoadWAV("Assets/Sound/SFX/Select.wav");

				Mix_VolumeChunk(Select, 10);
				Mix_VolumeMusic(32); //The volume for the music (0-255)
			}		}
	}

	const int xDim = 1080; 
	const int yDim = 720;  


	int minDim; //smallest dimension (used for scaling)
	if (xDim > yDim)
		minDim = yDim;
	else
		minDim = xDim;

	SDL_Log("Creating Window");
	SDL_Window* mainWindow = SDL_CreateWindow("Luke Howard #15623020 Games Programming", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, xDim, yDim, SDL_WINDOW_RESIZABLE);
	SDL_Log("Creating Renderer");
	SDL_Renderer* mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_Log("Creating Cursor");
	AH_Cursor* cursor = new AH_Cursor(mainRenderer, "Assets/Sprites/Cursor.png");

	int x, y;
	SDL_GetMouseState(&x, &y);
	SDL_Log("Mouse Location       x:%i y:%i", (int)x, (int)y);

	Board Level(mainRenderer,minDim,cursor);

	SDL_Log("Board Size In Pixels: %i", Level.getPixelBoardSize());
	
	//////////////////////Available Fonts//////////////////////
	//"Assets/Fonts/destructobeam-bb/destructobeambb_reg.ttf"
	//"Assets/Fonts/hydrogenwhiskey/hydrogen whiskey.ttf"
	//"Assets/Fonts/mainframe-bb/MAINBB__.ttf"
	//"Assets/Fonts/nasalization-free/nasalization-rg.ttf"
	///////////////////////////////////////////////////////////

	SDL_Log("Defining Colours");
	SDL_Color green = { 10,200,10 };
	SDL_Color red = { 250,10,0 };
	SDL_Color enemy = { 242,41,195 };
	SDL_Color player = { 94,206,255 };
	SDL_Log("Defining UI Elements");
	AH_Text* GameTimerText = new AH_Text(mainRenderer, "60000", "Assets/Fonts/destructobeam-bb/destructobeambb_reg.ttf", 100, red, Level.getPixelBoardSize(), 50, 150, 350);
	AH_Text* TurnTimerText = new AH_Text(mainRenderer, "6000", "Assets/Fonts/destructobeam-bb/destructobeambb_reg.ttf", 60, player, Level.getPixelBoardSize(), 250, 100, 175);
	AH_Sprite* TurnIcon = new AH_Sprite(mainRenderer, Level.getPixelBoardSize() + 200, 220, 150, 150, 1, 1, 150);
	TurnIcon->load("Assets/Sprites/Icon_Player.png");

	AH_Text* PlayerHPText = new AH_Text(mainRenderer, "HP: ", "Assets/Fonts/destructobeam-bb/destructobeambb_reg.ttf", 60, player, Level.getPixelBoardSize()+110, 380, 100, 175);
	AH_Sprite* PlayerIcon = new AH_Sprite(mainRenderer, Level.getPixelBoardSize() + 10, 380, 100, 100, 1, 1, 100);
	PlayerIcon->load("Assets/Sprites/Icon_Player.png");

	AH_Text* EnemyHPText = new AH_Text(mainRenderer, "HP: ", "Assets/Fonts/destructobeam-bb/destructobeambb_reg.ttf", 60, enemy, Level.getPixelBoardSize() + 110, 500, 100, 175);
	AH_Sprite* EnemyIcon = new AH_Sprite(mainRenderer, Level.getPixelBoardSize() + 10, 500, 100, 100, 1, 1, 100);
	EnemyIcon->load("Assets/Sprites/Icon_Enemy.png");

	AH_Text* ScoreText = new AH_Text(mainRenderer, "Score: ", "Assets/Fonts/destructobeam-bb/destructobeambb_reg.ttf", 60, green, Level.getPixelBoardSize() + 10, 610, 100, 350);

	AH_Text* VictoryText = new AH_Text(mainRenderer, "Victory!", "Assets/Fonts/destructobeam-bb/destructobeambb_reg.ttf", 60, player, 0, 200, 400, 800);
	AH_Text* DefeatText = new AH_Text(mainRenderer, "Defeat!", "Assets/Fonts/destructobeam-bb/destructobeambb_reg.ttf", 60, enemy, 0, 200, 400, 800);

	AH_Sprite* Title = new AH_Sprite(mainRenderer, 50, 10, 1042, 134, 1, 1, 1000);
	Title->load("Assets/Sprites/Metropolis.png");

	AH_Sprite* mainmenuStartButton = new AH_Sprite(mainRenderer, 390, 300, 300, 100, 1, 1, 300);
	mainmenuStartButton->load("Assets/Sprites/MenuStartButton.png");

	AH_Sprite* mainmenuExitButton = new AH_Sprite(mainRenderer, 390, 450, 300, 100, 1, 1, 300);
	mainmenuExitButton->load("Assets/Sprites/MenuExitButton.png");

	AH_Sprite* mainmenuControls = new AH_Sprite(mainRenderer, 0, 400, 500, 500, 1, 1, 400);
	mainmenuControls->load("Assets/Sprites/Controls.png");

	AH_Sprite* mainmenuControlsKeyBoard = new AH_Sprite(mainRenderer, xDim-200, 400, 500, 500, 1, 1, 400);
	mainmenuControlsKeyBoard->load("Assets/Sprites/Controls_KeyBoard.png");

	//bool playersTurn;
	
	bool gameEndTimerStarted = false;
	SDL_Log("Running");
	while (Running)
	{
		if (InMainMenu)
		{
			Mix_PlayMusic(BGM_menu, -1);
		}
		while (InMainMenu)
		{
			handleMenuEvents(cursor, InMainMenu, InGame,Running,Select);
			SDL_SetRenderDrawColor(mainRenderer, 1, 1, 1, 255);
			SDL_RenderClear(mainRenderer);
			SDL_Log("#######################NOW DOING UPDATING##########################");
			cursor->update();
			SDL_Log("#######################NOW DOING RENDERING##########################");
			Title->render();
			mainmenuStartButton->render();
			mainmenuExitButton->render();
			mainmenuControls->render();
			mainmenuControlsKeyBoard->render();
			cursor->render();

			SDL_RenderPresent(mainRenderer);
		}
		if (InGame)
		{
			Mix_HaltMusic();
			Mix_PlayMusic(BGM_game, 5);

			GameTimer.resetTimer();
			TurnTimer.resetTimer();
			//playersTurn = true;
		}
		while (InGame)
		{
			FrameTimer.resetTimer();

			SDL_SetRenderDrawColor(mainRenderer, 1, 1, 1, 255);
			SDL_RenderClear(mainRenderer);

			Level.handleEvents();//<--the board also handles input
			

			SDL_Log("#######################NOW DOING UPDATING##########################");
			if (TurnTimer.getTime() > 6000&&!gameEndTimerStarted)
			{
				TurnTimer.resetTimer();
				if (Level.isPlayerTurn())
				{
					TurnTimerText->setColour(enemy);
					TurnIcon->load("Assets/Sprites/Icon_Enemy.png");
				}
				else
				{
					TurnTimerText->setColour(player);
					TurnIcon->load("Assets/Sprites/Icon_Player.png");
				}

				Level.toggleTurn();
			}

			//testFlame.render();
			
			Level.update();
			cursor->update();

			GameTimerSTR.str("");
			GameTimerSTR << 60000 - GameTimer.getTime();
			//cout << "Game Timer: " << GameTimerSTR.str().c_str() << endl;

			TurnTimerSTR.str("");
			TurnTimerSTR << 6000 - TurnTimer.getTime();
			//cout << "Turn Timer: " << TurnTimerSTR.str().c_str() << endl;

			PlayerHPSTR.str("");
			PlayerHPSTR << "HP: " << Level.getPlayer()->getHP();

			EnemyHPSTR.str("");
			EnemyHPSTR << "HP: " << Level.getEnemy()->getHP();

			ScoreSTR.str("");
			ScoreSTR << "Score: " << Level.getScore();

			SDL_Log("Game Timer: %i",60000 - GameTimer.getTime());
			GameTimerText->setText(GameTimerSTR.str().c_str());
			GameTimerText->update();

			TurnTimerText->setText(TurnTimerSTR.str().c_str());
			TurnTimerText->update();

			PlayerHPText->setText(PlayerHPSTR.str().c_str());
			PlayerHPText->update();

			EnemyHPText->setText(EnemyHPSTR.str().c_str());
			EnemyHPText->update();

			ScoreText->setText(ScoreSTR.str().c_str());
			ScoreText->update();
			SDL_Log("#######################NOW DOING RENDERING##########################");
			Level.render();
			GameTimerText->render();
			TurnTimerText->render();
			TurnIcon->render();
			PlayerIcon->render();
			PlayerHPText->render();
			EnemyIcon->render();
			EnemyHPText->render();
			ScoreText->render();
			if (!Level.getEnemy()->isAlive())
			{
				if (!gameEndTimerStarted)
				{
					gameEndTimerStarted = true;
					GameEndTimer.resetTimer();
				}
				VictoryText->render();
			}
			if (!Level.getPlayer()->isAlive()|| GameTimer.getTime() > 60000)
			{
				if (!gameEndTimerStarted)
				{
					gameEndTimerStarted = true;
					GameEndTimer.resetTimer();
				}
				DefeatText->render();
			}

			cursor->render();

			SDL_RenderPresent(mainRenderer);


			if (FrameTimer.getTime() < DELTA_TIME)
			{
				SDL_Delay(DELTA_TIME - FrameTimer.getTime());
			}
			else
				SDL_Log("ERROR: Frame took longer than expected. %a ms\n", FrameTimer.getTime());

			

			if (gameEndTimerStarted&&GameEndTimer.getTime() > 3000)
			{
				InGame = false;
				InMainMenu = true;
			}

			
		}
		//SDL_Log("HELP");
	}
	Mix_FreeMusic(BGM_game);
	Mix_FreeMusic(BGM_menu);
	Mix_FreeChunk(Select);
	Mix_CloseAudio();

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}


void handleMenuEvents(AH_Cursor* cursor, bool &InMainMenu, bool &InGame, bool &Running, Mix_Chunk* Select)
{
	SDL_Log("#######################NOW HANDLING INPUT##########################");
	SDL_PollEvent(&MenuEvent);
	if (MenuEvent.type == SDL_MOUSEBUTTONDOWN && MenuEvent.key.repeat == NULL)
	{
		Mix_PlayChannel(-1, Select, 0);
		int cX = cursor->getX();
		int cY = cursor->getY();
		SDL_Log("Mouse click at x: %i y: %i", cX, cY);
		if (cX > 390 && cX < 690 && cY>300 && cY < 400)
		{
			InMainMenu = false;
			InGame = true;
		}
		if (cX > 390 && cX < 690 && cY>450 && cY < 550)
		{
			InMainMenu = false;
			InGame = false;
			Running = false;
		}

	}
}