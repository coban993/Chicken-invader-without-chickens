#include "framework\World.h"
#include "framework\Core.h"
#include "framework\Actor.h"

namespace wci
{
	World::World(Application* owningApp)
		:mOwningApp{ owningApp },
		mBeginPlay{false},
		mActors{},
		mPendingActors{}
	{
	}

	World::~World()
	{
	}

	void World::TickInternal(float deltaTime)
	{
		for (shared<Actor> actor : mPendingActors)
		{
			mActors.push_back(actor);
			actor->BeginPlayInternal();
		}

		mPendingActors.clear();
		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			if (iter->get()->IsPendingDestroyed())
				iter = mActors.erase(iter);
			else
			{
				iter->get()->TickInternal(deltaTime);
				++iter;
			}
		}

		Tick(deltaTime);
	}

	void World::Tick(float deltaTime)
	{
	}

	void World::BeginPlayingInternal()
	{
		if (!mBeginPlay)
		{
			mBeginPlay = true;
			BeginPLay();
		}
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto& actor : mActors)
		{
			actor->Render(window);
		}
	}

	void World::BeginPLay()
	{
	}
}