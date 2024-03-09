#include "enemy\UFOStage.h"
#include "framework\MathUtility.h"
#include "enemy\UFO.h"
#include "framework\World.h"
#include "framework\Core.h"
#include <iostream>

namespace wci
{
	UFOStage::UFOStage(World* world)
		:GameStage{world},
		mSpawnInterval{4.f},
		mSpawnAmount{2},
		mCurrentSpawnAmount{0},
		mUFOSpeed{200.f}
	{
	}

	void UFOStage::StartStage()
	{
		mSpawnTimer = TimeManager::Get().SetTimer(GetWeakRef(), &UFOStage::SpawnUFO, mSpawnInterval, true);
	}

	void UFOStage::StageFinished()
	{
		TimeManager::Get().ClearTimer(mSpawnTimer);
	}

	sf::Vector2f UFOStage::GetRandomSpawnLocation() const
	{
		auto windowSize = GetWorld()->GetWindowSize();
		float spawnLeft = RandomRange(-1, 1);
		float spawnLocX = 0;

		if (spawnLeft < 0)
			spawnLocX = windowSize.x + 100.f;
		else
			spawnLocX = -100.f;

		float spawnLocY = RandomRange(0, windowSize.y);

		return sf::Vector2f{ spawnLocX, spawnLocY };
	}

	void UFOStage::SpawnUFO()
	{
		sf::Vector2f spawnLoc = GetRandomSpawnLocation();
		auto windowSize = GetWorld()->GetWindowSize();
		sf::Vector2f center{ windowSize.x / 2.f, windowSize.y / 2.f };
		sf::Vector2f spawnLocToCenter{ center.x - spawnLoc.x, center.y - spawnLoc.y };
		Normalize(spawnLocToCenter);

		sf::Vector2f spawnVelocity = spawnLocToCenter * mUFOSpeed;

		weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>(spawnVelocity);
		newUFO.lock()->SetActorLocation(spawnLoc);	

		if (++mCurrentSpawnAmount == mSpawnAmount)
			FinishStage();
	}
}