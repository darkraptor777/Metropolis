#pragma once
#include "Entity.h"
class Cover :
	public Entity
{
public:
	Cover(double percent);
	~Cover();

	float getPercent() { return percent; };
	void setPercent(double p) { if (p >= 0 && p <= 1)percent = p; };

private:
	float percent; //percentage of cover (half cover, full cover etc.)
};

