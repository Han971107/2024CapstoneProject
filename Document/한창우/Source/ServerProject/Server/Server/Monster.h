#pragma once
#include "Creature.h"

/*-----------
	Server
-------------*/

class Monster : public Creature
{
	using Super = Creature;

public:
	Monster();
	virtual ~Monster();

	virtual void Update();
};

