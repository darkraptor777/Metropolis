#pragma once
#include "Entity.h"
class Floor :
	public Entity
{
public:
	Floor(SDL_Renderer* ren,int x, int y, int pixelUnitSize);
	~Floor();
};

