#pragma once
#include "SDL.h"
#include "AH_Sprite.h"
#include <iostream>
#include <string>

using namespace std;

class Entity
{
public:
	Entity();
	Entity(Entity &obj);
	Entity(SDL_Renderer* renderer);
	Entity(SDL_Renderer* renderer, int maxHP, string name, bool pathable);
	Entity(SDL_Renderer* renderer, int hp, int maxHP, string name, bool pathable);
	Entity(SDL_Renderer* ren, int x, int y, int hp, int maxHP, string name, bool pathable, bool alive, bool seen, bool visible, const char* spritepath, int spritewidth, int spriteheight, int totalframes, int framerate, int pixelUnitSize);
	~Entity();
	void TakeDamage(int dmg);
	void Heal(int health);
	void loadSprite(const char* filepath);
	void loadSprite(SDL_Renderer* renderer, const char* filepath, int x, int y, int spriteWidth, int spriteHeight, int totalFrames, int frameRate, int pixelUnitSize);

	virtual Entity* clone();

	virtual void update();
	virtual void render();

	void setX(int a) { x = a; sprite->setX(a*20); };
	void setY(int b) { y = b; sprite->setY(b*20); };

	int getX() { return x; };
	int getY() { return y; };
	int getMaxHP() { return maxHP; };
	int getHP() { return hp; };
	string getName() { return name; };
	bool isAlive() { return alive; };
	bool isVisible() { return visible; };
	bool isSeen() { return seen; };
	bool isPathable() { return pathable; };
	AH_Sprite* getSprite() { return sprite; };

protected:
	void reconstruct(SDL_Renderer* ren, int x, int y, int hp, int maxHP, string name, bool pathable, bool alive, bool seen, bool visible, const char* spritepath, int spritewidth, int spriteheight, int totalframes, int framerate, int pixelUnitSize);

private:
	int x;
	int y;
	int hp;
	int maxHP;
	bool pathable;
	bool alive;
	bool seen; //has it been seen at any point
	bool visible; //can it currently be seen
	string name; //name of entity
	AH_Sprite* sprite; 
	//SDL_Renderer* renderer;
};

