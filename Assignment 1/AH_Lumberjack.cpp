#include "pch.h"
#include "AH_Lumberjack.h"

//has to be used because timber is a class function which breaks it if you try to pass it directly
static void LogFunc(void* userData, int category, SDL_LogPriority priority, const char* message) 
{
	Lumberjack* temp = (Lumberjack*)userData; //take the user data an recast it as a lumberjack
	temp->Timber(userData, category, priority, message); //then pass the recast information to timber
}

Lumberjack::Lumberjack(const string& filePath)
{
	logFile.open(filePath);

	if (!Lumberjack::logFile.is_open())
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Couldn't open file"); //uh oh

	SDL_LogSetOutputFunction(&LogFunc, (void *)this);
}


Lumberjack::~Lumberjack()
{
	logFile.close();
}

//commenting "timber" with a bunch of exclamation marks seems redundant
//TIMBERRRRRRR!!!!!!!!
void Lumberjack::Timber(void* userData, int category, SDL_LogPriority priority, const char* message)
{
	cout << message << endl;

	logFile << message << endl;
}