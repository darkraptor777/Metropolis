#include "pch.h"
#include "AH_Sprite.h"

AH_Sprite::AH_Sprite()
{
	SDL_Log("default sprite constructor called.");
	SDL_Log("WARNING: NO RENDERER ASSIGNED.");
	this->x = 0;
	this->y = 0;
	frameWidth = 60;
	frameHeight = 60;
	frameIndex = 0;
	this->totalFrames = 1;
	this->frameRate = 6;
}

AH_Sprite::AH_Sprite(AH_Sprite &obj)
{
	SDL_Log("copy sprite constructor called.");
	this->x = obj.getX();
	this->y = obj.getY();
	frameWidth = obj.getWidth();
	frameHeight = obj.getHeight();
	frameIndex = obj.getFrameIndex();
	this->totalFrames = obj.getTotalFrames();
	this->frameRate = obj.getFrameRate();
	this->renderer = &(*obj.getRenderer());
	this->scaler = obj.getScaler();
	delete texture;
	this->path = obj.getPath();
	SDL_Log(path);
	load(path);
}

AH_Sprite::AH_Sprite(SDL_Renderer* ren)
{
	SDL_Log("basic parameterised sprite constructor called.");
	this->x = 0;
	this->y = 0;
	frameWidth = 20;
	frameHeight = 20;
	frameIndex = 0;
	this->totalFrames = 1;
	this->frameRate = 6;

	renderer = ren;
}

AH_Sprite::AH_Sprite(SDL_Renderer* ren,int x,int y,int width,int height,int totalFrames,int frameRate,int pixelUnitSize)
{
	SDL_Log("advanced parameterised sprite constructor called.");
	this->x = x;
	this->y = y;
	frameWidth = width;
	frameHeight = height;
	frameIndex = 0;
	this->totalFrames = totalFrames;
	this->frameRate = frameRate;
	this->renderer = renderer;
	renderer = ren;
	if (width >= height)
		scaler = (double)pixelUnitSize / (double)width;
	else
		scaler = (double)pixelUnitSize / (double)height; 	
}


AH_Sprite::~AH_Sprite()
{
	SDL_Log("default sprite destructor called.");
	SDL_DestroyTexture(texture);
}


void AH_Sprite::render()//////////////////////////////////////////////////////////////////////////////
{
	unsigned int ticks = SDL_GetTicks();
	frameIndex = (ticks/frameRate) % totalFrames;
	SDL_Rect src = { 0,0,frameWidth,frameHeight }; //position of sprite in texture file
	//SDL_Log("Scaler: %d", scaler);
	//SDL_Log("drawing sprite from x: %d y %d to x: %d y: %d", (x*scaler), (y*scaler), (frameWidth*scaler), (frameHeight*scaler));
	SDL_Rect dest = {(x*scaler), (y*scaler), frameWidth*scaler, frameHeight*scaler}; 
	SDL_RenderCopy(renderer, texture, &src, &dest);

}
void AH_Sprite::update()
{

}

void AH_Sprite::reload()
{
	SDL_Log("Attempting to reload texture from %s\n", path);
	SDL_Surface* surface = IMG_Load(path);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
	{
		SDL_Log("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
	}
	else
	{
		SDL_Log("Reload of %s successful!\n", path);
	}

	SDL_FreeSurface(surface);
}

void AH_Sprite::load(const char* filepath)
{
	path = filepath;
	SDL_Log("Attempting to load new texture from %s\n", path);
	SDL_Surface* surface = IMG_Load(filepath);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
	{
		SDL_Log("Unable to create texture from %s! SDL Error: %s\n", filepath, SDL_GetError());
	}
	else
	{
		SDL_Log("Loaded %s successfully!\n", path);
	}

	SDL_FreeSurface(surface);
}
