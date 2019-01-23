#pragma once
#include "Cover.h"
class Wall :
	public Cover
{
public:
	Wall(SDL_Renderer* ren, int x, int y, int pixelBoardSize);
	~Wall();
};

