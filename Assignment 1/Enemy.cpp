#include "pch.h"
#include "Enemy.h"


Enemy::Enemy(SDL_Renderer* renderer, int x, int y, int hp, int maxHP, string name, bool pathable, bool alive, bool seen, bool visible, const char* spritepath, int spritewidth, int spriteheight, int totalframes, int framerate, int pixelUnitSize, bool canShoot, bool canMelee, int maxMovement):Character(renderer, x, y, hp, maxHP, name, pathable, alive, seen, visible, spritepath, spritewidth, spriteheight, totalframes, framerate, pixelUnitSize, canShoot, canMelee, maxMovement)
{
}


Enemy::~Enemy()
{
}


void Enemy::TakeTurn()
{

}
