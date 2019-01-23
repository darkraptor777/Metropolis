#include "pch.h"
#include "Entity.h"

Entity::Entity()
{
	SDL_Log("default entity constructor called. ");
	//this->renderer = renderer;
	hp = 0;
	maxHP = 0;
	alive = false;
	seen = false;
	visible = false;
	pathable = false;
	name = "undefined";
}

Entity::Entity(Entity &obj)
{
	this->x = obj.getX();
	this->y = obj.getY();
	this->hp = obj.getHP();
	this->maxHP = obj.getMaxHP();
	this->pathable = obj.isPathable();
	this->alive = obj.isAlive();
	this->seen = obj.isSeen();
	this->visible = obj.isVisible();
	this->name = obj.getName();
	delete sprite;
	sprite = new AH_Sprite(*(obj.getSprite()));
}

Entity::Entity(SDL_Renderer* renderer)
{
	SDL_Log("basic entity constructor called. ");
	//this->renderer = renderer;
	hp = 0;
	maxHP = 0;
	alive = false;
	seen = false;
	visible = false;
	pathable = false;
	name = "undefined";
	sprite=new AH_Sprite(renderer); 
}

Entity::Entity(SDL_Renderer* renderer, int hp, int maxHP, string name, bool pathable=false)
{
	SDL_Log("paramaterised entity constructor called. ");
	//this->renderer = renderer;
	this->hp = hp;
	this->maxHP = maxHP;
	this->pathable = pathable;
	alive = true;
	seen = false;
	visible = false;
	this->name = name;
	sprite = new AH_Sprite(renderer);
}

Entity::Entity(SDL_Renderer* renderer, int maxHP, string name, bool pathable = false)
{
	SDL_Log("paramaterised entity constructor called. ");
	//this->renderer = renderer;
	this->hp = maxHP;
	this->maxHP = maxHP;
	this->pathable = pathable;
	alive = true;
	seen = false;
	visible = false;
	this->name = name;
	sprite = new AH_Sprite(renderer);
}

Entity::Entity(SDL_Renderer* ren, int x, int y, int hp, int maxHP, string name, bool pathable, bool alive, bool seen, bool visible, const char* spritepath, int spritewidth, int spriteheight, int totalframes, int framerate, int pixelUnitSize)
{
	SDL_Log("entity full constructor called.");
	this->x = x;
	this->y = y;
	this->hp = maxHP;
	this->maxHP = maxHP;
	this->pathable = pathable;
	this->alive = alive;
	this->seen = seen;
	this->visible = visible;
	this->name = name;
	delete sprite;
	sprite = new AH_Sprite(ren, x, y, spritewidth, spriteheight, totalframes, framerate, pixelUnitSize);
	loadSprite(spritepath);
}

Entity* Entity::clone() { return new Entity(*this); };

void Entity::reconstruct(SDL_Renderer* ren, int x, int y, int hp, int maxHP, string name, bool pathable, bool alive, bool seen, bool visible, const char* spritepath,int spritewidth,int spriteheight,int totalframes,int framerate,int pixelUnitSize)
{
	SDL_Log("entity reconstructor called.");
	this->x = x;
	this->y = y;
	this->hp = maxHP;
	this->maxHP = maxHP;
	this->pathable = pathable;
	this->alive = alive;
	this->seen = seen;
	this->visible = visible;
	this->name = name;
	delete sprite;
	sprite = new AH_Sprite(ren,x,y,spritewidth,spriteheight,totalframes,framerate,pixelUnitSize);
	loadSprite(spritepath);
}


void Entity::update()
{

}

void Entity::render()
{
	SDL_Log("Rendering Entity: %s",name.c_str());
	if(alive)
		sprite->render();
}

void Entity::TakeDamage(int dmg)
{
	SDL_Log("Entity %s has %i HP!", name.c_str(),hp);
	SDL_Log("Entity %s takes %i damage!", name.c_str(),dmg);
	hp -= dmg;
	if (hp <= 0)
		hp = 0;
	if (hp == 0)
	{
		alive = false;
		SDL_Log("Entity %s dies!", name.c_str());
	}
}

void Entity::Heal(int health)
{
	hp += health;
	if (hp > maxHP)
		hp = maxHP;
}

void Entity::loadSprite(const char* filepath)
{
	SDL_Log("Loading %s Sprite", name.c_str());
	sprite->load(filepath);
}

void Entity::loadSprite(SDL_Renderer* renderer, const char* filepath, int x, int y, int spriteWidth, int spriteHeight, int totalFrames, int frameRate, int pixelUnitSize)
{
	SDL_Log("Loading %s Sprite", name.c_str());
	delete sprite;
	sprite = new AH_Sprite(renderer, x, y, spriteWidth, spriteHeight, totalFrames, frameRate, pixelUnitSize);
	sprite->load(filepath);
}

Entity::~Entity()
{
	SDL_Log("default entity destructor called.");
	delete sprite;
}
