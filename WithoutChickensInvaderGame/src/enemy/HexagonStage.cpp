#include "enemy\HexagonStage.h"
#include "enemy\Hexagon.h"
#include "framework\World.h"

namespace wci
{
	HexagonStage::HexagonStage(World* world)
		:GameStage{world},
		mSpawnInterval{5.f},
		mSideSpawnOffset{80.f},
		mSpawnGroupAmount{5},
		mCurrentSpawnCount{0},
		mMidSpawnLocation{world->GetWindowSize().x/2.f, -100.f},
		mRightSpawnLocation{world->GetWindowSize().x/2.f + mSideSpawnOffset, -100.f - mSideSpawnOffset},
		mLeftSpawnLocation{world->GetWindowSize().x/2.f - mSideSpawnOffset, -100.f - mSideSpawnOffset}
	{
	}

	void HexagonStage::StartStage()
	{
		mSpawnTimer = TimeManager::Get().SetTimer(GetWeakRef(), &HexagonStage::SpawnHexagon, mSpawnInterval, true);
	}

	void HexagonStage::StageFinished()
	{
		TimeManager::Get().ClearTimer(mSpawnTimer);
	}

	void HexagonStage::SpawnHexagon()
	{
		weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(mMidSpawnLocation);

		newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(mLeftSpawnLocation);

		newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(mRightSpawnLocation);

		if (++mCurrentSpawnCount == mSpawnGroupAmount)
			FinishStage();
	}
}