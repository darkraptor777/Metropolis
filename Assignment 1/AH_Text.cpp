#include "pch.h"
#include "AH_Text.h"


AH_Text::AH_Text(SDL_Renderer* ren, const char* text, const char* path, int size, SDL_Color colour,int x,int y, int height, int width)
{
	SDL_Log("default text constructor called.");
	renderer = ren;
	this->text = (char*)text;
	this->path = path;
	this->size = size;
	this->colour = colour;
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;

	reload();
}


AH_Text::~AH_Text()
{
	SDL_Log("default text destructor called.");
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
}

void AH_Text::update()
{
	if(texture!=NULL)
		SDL_DestroyTexture(texture);
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), colour);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
	{
		SDL_Log("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
	}

	SDL_FreeSurface(surface);
}

void AH_Text::render()
{
	SDL_Rect src = { 0, 0, this->width, this->height };
	SDL_Rect dst = { this->x, this->y, this->width, this->height };
	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void AH_Text::reload()
{
	//if (texture != NULL)
		//delete texture;
	font = TTF_OpenFont(path, size);
	SDL_Surface* surface = TTF_RenderText_Solid(font,text.c_str(),colour);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
	{
		SDL_Log("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
	}

	SDL_FreeSurface(surface);
}