#include "pch.h"
#include "Cover.h"


Cover::Cover(double p)
{
	SDL_Log("default cover constructor called.");
	percent = p;
}


Cover::~Cover()
{
	SDL_Log("default cover destructor called.");
}
