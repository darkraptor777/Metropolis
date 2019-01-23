#include "pch.h"
#include "AH_Cursor.h"


AH_Cursor::AH_Cursor(SDL_Renderer* ren, const char* filepath)
{
	SDL_Log("cursor constructor called.");
	SDL_ShowCursor(SDL_DISABLE);
	SDL_GetMouseState(&x, &y);

	cursor = new AH_Sprite(ren, (int)x, (int)y, 20, 20, 1, 1, 20);
	cursor->load(filepath);
}


AH_Cursor::~AH_Cursor()
{
	SDL_Log("cursor destructor called.");
	delete cursor;
}


int AH_Cursor::getX()
{
	return (int)x;
}
int AH_Cursor::getY()
{
	return (int)y;
}
bool AH_Cursor::leftMouse()
{
	return SDL_BUTTON(SDL_BUTTON_LEFT);
}
bool AH_Cursor::rightMouse()
{
	return SDL_BUTTON(SDL_BUTTON_RIGHT);
}

void AH_Cursor::update()
{
	SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);
	SDL_Log("Cursor at x:%i y:%i",(int)x, (int)y);
	cursor->setX((int)x);
	cursor->setY((int)y);
}

void AH_Cursor::render()
{
	cursor->render();
}