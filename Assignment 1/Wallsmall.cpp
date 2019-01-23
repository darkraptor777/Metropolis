#include "pch.h"
#include "Wallsmall.h"


Wallsmall::Wallsmall(SDL_Renderer* ren, int x, int y, int pixelBoardSize):Cover(0.3)
{
	reconstruct(ren, x*20, y*20, 0, 0, "Wallsmall", false, true, true, true, "Assets/Sprites/Wallsmall.png", 20, 20, 1, 10, pixelBoardSize);
}


Wallsmall::~Wallsmall()
{
}
