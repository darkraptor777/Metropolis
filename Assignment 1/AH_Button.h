#pragma once
#include"AH_Sprite.h"
#include "AH_Text.h"

class AH_Button
{
public:
	AH_Button(SDL_Renderer* ren, int x, int y, const char* spritePath, const char* text, const char* fontPath, int size, SDL_Color colour, int height, int width);
	~AH_Button();



private:
	AH_Sprite* buttonSprite=nullptr;
	AH_Text* buttonText = nullptr;
	int x;
	int y;
};

