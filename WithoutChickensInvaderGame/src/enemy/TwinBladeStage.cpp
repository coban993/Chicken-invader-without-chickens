#include "enemy\TwinBladeStage.h"
#include "framework\World.h"
#include "enemy\TwinBlade.h"

namespace wci
{
	TwinBladeStage::TwinBladeStage(World* world)
		:GameStage{world},
		mSpawnInterval{1.5f},
		mSpawnDistanceToCenter{100.f},
		mLeftSpawnLocation{world->GetWindowSize().x/2.f - mSpawnDistanceToCenter, -100.f},
		mRightSpawnLocation{world->GetWindowSize().x/2.f + mSpawnDistanceToCenter, -100.f},
		mSpawnLocation{mLeftSpawnLocation},
		mSpawnAmount{10},
		mCurrentSpawnCount{0}
	{
	}

	void TwinBladeStage::StartStage()
	{
		mSpawnTimerHandle = TimeManager::Get().SetTimer(GetWeakRef(), &TwinBladeStage::SpawnTwinBlade, mSpawnInterval, true);
	}
	
	void TwinBladeStage::SpawnTwinBlade()
	{
		weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
		newTwinBlade.lock()->SetActorLocation(mSpawnLocation);

		if (mSpawnLocation == mLeftSpawnLocation)
			mSpawnLocation = mRightSpawnLocation;
		else
			mSpawnLocation = mLeftSpawnLocation;

		++mCurrentSpawnCount;

		if (mCurrentSpawnCount == mSpawnAmount)
			FinishStage();
	}

	void TwinBladeStage::StageFinished()
	{
		TimeManager::Get().ClearTimer(mSpawnTimerHandle);
	}
}