#include "pch.h"
#include "Wall.h"


Wall::Wall(SDL_Renderer* ren, int x, int y, int pixelBoardSize):Cover(0.6)
{
	reconstruct(ren, x*20, y*20, 0, 0, "Wall", false, true, true, true, "Assets/Sprites/Wall.png", 20, 20, 1, 10, pixelBoardSize);
}


Wall::~Wall()
{
}
