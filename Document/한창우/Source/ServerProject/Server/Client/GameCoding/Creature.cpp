#include "pch.h"
#include "Creature.h"
#include "SceneManager.h"
#include "DevScene.h"

Creature::Creature()
{
}

Creature::~Creature()
{
}

void Creature::BeginPlay()
{
	Super::BeginPlay();

	// TODO

}

void Creature::Tick()
{
	Super::Tick();

	// TODO

}

void Creature::Render(HDC hdc)
{
	Super::Render(hdc);

	// TODO

}

void Creature::OnDamaged(Creature* attacker)
{
	if (attacker == nullptr)
		return;

	Stat& attackerStat = attacker->GetStat();
	Stat& stat = GetStat();

	int32 damage = attackerStat.attack - stat.defence;
	if (damage <= 0)
		return;

 	stat.hp = max(0, stat.hp - damage);

	if (stat.hp <= 0)
	{
		Scene* scene = GET_SINGLE(SceneManager)->GetCurrentScene();
		if (scene)
		{
 			scene->RemoveActor(this);
		}
	}
}
