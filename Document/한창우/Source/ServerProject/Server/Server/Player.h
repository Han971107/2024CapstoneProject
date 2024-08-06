#pragma once
#include "Creature.h"

/*-----------
	Server
-------------*/

class Player : public Creature
{
	using Super = Creature;

public:
	Player();
	virtual ~Player();

public:
	GameSessionRef session;
};

