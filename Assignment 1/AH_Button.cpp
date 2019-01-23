#include "pch.h"
#include "AH_Button.h"


AH_Button::AH_Button(SDL_Renderer* ren, int x, int y, const char* spritePath, const char* text, const char* fontPath, int size, SDL_Color colour, int height, int width)
{
	this->x = x;
	this->y = y;
	buttonSprite = new AH_Sprite(ren, x, y, height, width, 1, 1, x);
}


AH_Button::~AH_Button()
{
	delete buttonSprite;
}
