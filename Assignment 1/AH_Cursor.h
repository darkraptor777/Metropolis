#pragma once
#include "AH_Sprite.h"

class AH_Cursor
{
public:
	AH_Cursor(SDL_Renderer* ren, const char* filepath);
	~AH_Cursor();
	int getX();
	int getY();
	bool leftMouse();
	bool rightMouse();

	void update();
	void render();

private:
	int x;
	int y;
	AH_Sprite* cursor;
};

