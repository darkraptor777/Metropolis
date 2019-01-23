#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <iostream>

class AH_Text
{
public:
	AH_Text(SDL_Renderer* ren, const char* text, const char* path, int size, SDL_Color colour, int x, int y, int height, int width);
	~AH_Text();

	void setText(const char* text) { 
		this->text = text; 
	};
	void setColour(SDL_Color colour) { this->colour=colour; };
	void setSize(int s) { size = s; };
	void update();
	void render();
	void reload();

private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	const char* path;
	std::string text;
	int size;
	SDL_Color colour = { 0,0,0 };
	SDL_Texture* texture;
	int x, y;
	int height, width;
};

