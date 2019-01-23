#pragma once
#include "Cover.h"
class Wallsmall :
	public Cover
{
public:
	Wallsmall(SDL_Renderer* ren, int x, int y, int pixelBoardSize);
	~Wallsmall();
};

