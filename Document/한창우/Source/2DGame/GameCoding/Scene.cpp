#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "UI.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Init()
{
	// 원래 게임이 시작하면 시작해야 함
	{
		for (const vector<Actor*>& actors : _actors)
			for (Actor* actor : actors)
				actor->BeginPlay();

		for (UI* ui : _uis)
			ui->BeginPlay();
	}
}

void Scene::Update()
{
	for (const vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->Tick();

	for (UI* ui : _uis)
		ui->Tick();

	GET_SINGLE(CollisionManager)->Update();
}

void Scene::Render(HDC hdc)
{
	for (const vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->Render(hdc);

	for (UI* ui : _uis)
		ui->Render(hdc);
}

void Scene::AddActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	_actors[actor->GetLayer()].push_back(actor);
}

void Scene::RemoveActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	vector<Actor*>& v = _actors[actor->GetLayer()];
	auto findIt = std::find(v.begin(), v.end(), actor);
	if (findIt == v.end())
		return;

	v.erase(findIt);
}
