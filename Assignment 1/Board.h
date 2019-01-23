#pragma once

#include <math.h>
#include "AH_Cursor.h"
#include "AH_Sprite.h"
#include"Entity.h"
#include"Floor.h"
#include"Wall.h"
#include"Wallsmall.h"
#include "Character.h"
#include <cstdlib>
#include <time.h>

#include "SDL_mixer.h"

class Board
{
public:
	Board(SDL_Renderer* renderer,int pixelBoardSize, AH_Cursor* cursor);
	~Board();

	void render();
	void update();
	void handleEvents();

	bool tryMove(int a, int b);
	void moveEntity(SDL_Renderer* renderer, int a, int b); //move an entity form one location to another
	bool checkMove(int a,int b); //checks if entity can be moved to given location
	bool canReachFrom(int a, int b, int range); // checks if if an entity can reach another location

	bool tryShoot(int a, int b);

	int getDistance(int a, int b); //distance between two points
	int getPixelBoardSize() { return pixelBoardSize; };
	bool raycast(int sPoint, int ePoint, int &hitOne, int &hitTwo);

	void toggleTurn();
	bool isPlayerTurn() { return playerTurn; };

	void aiConsiderMove();

	int getDim() { return dim; };
	Entity* getEnemy() { return grid[enemy]; };
	Entity* getPlayer() { return grid[player]; };

	int getScore() { return score; };
	

private:
	Entity* grid[20 * 20];

	static SDL_Event currentEvent;

	int player=0;
	bool playerTurn = true;

	int enemy;

	int score = 0;

	int dim = 20; //how big the board is in indexes 
	int pixelBoardSize; //how big the board is in pixels
	AH_Cursor* cursor=nullptr;
	AH_Sprite* hoverSprite = nullptr;
	SDL_Renderer* renderer;
	Mix_Chunk* Shoot = nullptr;
	Mix_Chunk* Select = nullptr;
};

