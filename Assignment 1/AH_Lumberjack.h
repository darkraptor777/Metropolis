#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <SDL.h>
using namespace std;

class Lumberjack
{
public:
	Lumberjack(const std::string& filePath);
	~Lumberjack(void);
	void Timber(void* userData, int category, SDL_LogPriority priority, const char* message);

private:
	std::ofstream logFile;
};

