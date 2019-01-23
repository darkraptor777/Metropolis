#include "pch.h"
#include "Character.h"

Character::Character()
{
	SDL_Log("default character contructor called.");
}

Character::Character(Character &obj) : Entity(obj)
{
	SDL_Log("copy character contructor called.");
	this->canShoot = obj.getCanShoot();
	this->canMelee = obj.getCanMelee();
	this->maxMovement = obj.getMaxMovement();
	this->actions = obj.getActions();
	this->maxActions = obj.getMaxActions();
}

Character::Character(SDL_Renderer* renderer, int x, int y, int hp, int maxHP, string name, bool pathable, bool alive, bool seen, bool visible, const char* spritepath, int spritewidth, int spriteheight, int totalframes, int framerate, int pixelUnitSize, bool canShoot, bool canMelee, int maxMovement) : Entity(renderer, x, y, hp, maxHP, name, pathable, alive, seen, visible, spritepath, spritewidth, spriteheight, totalframes, framerate, pixelUnitSize)
{
	SDL_Log("paramaterised character contructor called.");
	this->canShoot = canShoot;
	this->canMelee = canMelee;
	this->maxMovement = maxMovement;
	this->actions = 2;
	this->maxActions = 2;
	
}


Character::~Character()
{
	SDL_Log("default character destructor called.");
}


Character* Character::clone() { return new Character(*this); };

void Character::update()
{

}

void Character::refreshActions()
{
	actions = maxActions;
}

void Character::useActions(int i)
{
	actions -= i;
	if (actions < 0)
		actions = 0;
}


void Character::Move(int &x, int&y)
{
	int selectedX, selectedY;
	bool signX, signY;
	selectedX = rand() % (getMaxMovement() + 1); //rand is not inclusive
	selectedY = rand() % (getMaxMovement() + 1);
	if (rand() % 1 == 0)
		signX = true;
	else
		signX = false; //negative number
	if (!signX)
		selectedX = -selectedX;

	if (rand() % 1 == 0)
		signY = true;
	else
		signY = false; //negative number
	if (!signY)
		selectedY = -selectedY;

	x = selectedX;
	y = selectedY;
}


/*
void Character::shoot(Entity* grid, int target)
{

}
void Character::melee(Entity* grid, int target)
{

}
*/