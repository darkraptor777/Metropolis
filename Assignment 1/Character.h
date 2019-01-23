#pragma once
#include "Entity.h"
#include <cstdlib>

class Character :
	public Entity
{
public:
	Character();
	Character(Character &obj);
	Character(SDL_Renderer* renderer, int x, int y, int hp, int maxHP, string name, bool pathable, bool alive, bool seen, bool visible, const char* spritepath, int spritewidth, int spriteheight, int totalframes, int framerate, int pixelUnitSize, bool canShoot, bool canMelee, int maxMovement);
	~Character();

	virtual Character* clone();
	virtual void update();

	void refreshActions();
	void useActions(int i);


	//void shoot(int target);
	//void melee(int target);

	bool getCanShoot() { return canShoot; };
	bool getCanMelee() { return canMelee; };
	int getMaxMovement() { return maxMovement; };
	int getActions() { return actions; };
	int getMaxActions() { return maxActions; };
	int getDamage() { return damage; };

	//AI section
	void Move(int &x, int&y);

protected:
	bool canShoot;
	bool canMelee;
	int maxMovement=4;
	int actions=2;
	int maxActions=2;
	int damage = 3;
};

