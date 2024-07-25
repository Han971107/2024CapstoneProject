#include "pch.h"
#include "Missile.h"
#include "TimeManager.h"
#include "ObjectManager.h"

Missile::Missile() : Object(ObjectType::Projectile)
{
}

Missile::~Missile()
{
}

void Missile::Init()
{
	// TODO : Data
	_stat.hp = 1;
	_stat.maxHp = 1;
	_stat.speed = 600;
}

void Missile::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	//
	if (_target == nullptr)
	{
		_pos.x += _stat.speed * deltaTime * ::cos(_angle);
		_pos.y -= _stat.speed * deltaTime * ::sin(_angle);

		_sumTime += deltaTime;
		if (_sumTime >= 0.2f)
		{
			const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();
			for (Object* obj : objects)
			{
				if (obj->GetObjectType() == ObjectType::Monster)
				{
					_target = obj;
					break; 
				}
			}
		}
	}
	else
	{
		Vector dir = _target->GetPos() - GetPos();
		dir.Normalize();

		Vector moveDir = dir * _stat.speed* deltaTime;
		_pos += moveDir;
	}

	// Ãæµ¹
	const auto objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (auto obj : objects)
	{ 
		if (this == obj)
			continue;

		if (obj->GetObjectType() != ObjectType::Monster)
			continue;

		Pos p1 = GetPos();
		Pos p2 = obj->GetPos();

		const float dx = p1.x - p2.x;
		const float dy = p1.y - p2.y;
		float dist = sqrt(dx * dx + dy * dy);

		if (dist < 25)
		{
			GET_SINGLE(ObjectManager)->Remove(obj);		// ±¦ÂúÀ»±î..?
			GET_SINGLE(ObjectManager)->Remove(this);	// ±¦ÂúÀ»±î..?
			return;
		}
	}

	// TODO
	if (_pos.y < -100)
	{
		// ±¦ÂúÀ»±î..?
		GET_SINGLE(ObjectManager)->Remove(this);
		return;
	}
}

void Missile::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 25);
}
