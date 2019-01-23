#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>


class AH_Sprite
{
public:
	AH_Sprite();
	AH_Sprite(AH_Sprite &obj);
	AH_Sprite(SDL_Renderer* renderer);
	AH_Sprite(SDL_Renderer* renderer, int x, int y, int width, int height, int totalFrames, int frameRate, int pixelUnitSize);
	~AH_Sprite();

	void render();
	void update();
	void load(const char* filepath);
	void reload();


	void setX(int x) { this->x = x; };
	void setY(int y) { this->y = y; };

	const char* getPath() { return path; };
	int getX() { return x; };
	int getY() { return y; };
	int getWidth() { return frameWidth; };
	int getHeight() { return frameHeight; };
	double getScaler() { return scaler; };
	unsigned int getFrameRate() { return frameRate; };
	unsigned int getFrameIndex() { return frameIndex; };
	unsigned int getTotalFrames() { return totalFrames; };
	SDL_Texture* getTexture() { return texture; };
	SDL_Renderer* getRenderer() { return renderer; };

private:
	SDL_Renderer* renderer=nullptr;
	SDL_Texture* texture;

	const char* path;

	unsigned int frameRate;
	unsigned int frameIndex;
	unsigned int totalFrames; //total number of frames for sequence

	int x, y;
	int frameWidth, frameHeight;
	double scaler=1;
};

