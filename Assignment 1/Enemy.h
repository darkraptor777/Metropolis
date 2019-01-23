#pragma once
#include "Character.h"

class Enemy :
	public Character
{
public:
	Enemy(SDL_Renderer* renderer, int x, int y, int hp, int maxHP, string name, bool pathable, bool alive, bool seen, bool visible, const char* spritepath, int spritewidth, int spriteheight, int totalframes, int framerate, int pixelUnitSize, bool canShoot, bool canMelee, int maxMovement);
	~Enemy();
	void TakeTurn();
};

