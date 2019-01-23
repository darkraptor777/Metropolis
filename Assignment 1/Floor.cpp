#include "pch.h"
#include "Floor.h"


Floor::Floor(SDL_Renderer* ren,int x,int y,int pixelUnitSize)
{
	reconstruct(ren, x*20, y*20, 0, 0, "Floor", true, true, true, true, "Assets/Sprites/Floor.png",20,20,1,10,pixelUnitSize);
}


Floor::~Floor()
{
}
