#ifndef TimerFILE
#define TimerFile

#pragma once
#include <iostream>
#include <SDL.h>

class Timer
{
private:
	int startTime;
public:
	Timer();
	~Timer();
	void resetTimer();
	int getTime();
};

#endif