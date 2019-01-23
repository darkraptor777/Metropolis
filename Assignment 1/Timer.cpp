#include "pch.h"
#include "Timer.h"


Timer::Timer()
{
	SDL_Log("Timer constructor called.");
	startTime = 0;
}


Timer::~Timer()
{
	SDL_Log("Timer destructor called.");
}

void Timer::resetTimer()
{
	startTime = SDL_GetTicks();
}

int Timer::getTime()
{
	return (SDL_GetTicks() - startTime);
}
