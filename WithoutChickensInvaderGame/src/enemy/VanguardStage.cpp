#include "enemy\VanguardStage.h"
#include "framework\World.h"
#include "enemy\Vanguard.h"

namespace wci
{
	VanguardStage::VanguardStage(World* world)
		:GameStage{world},
		mSpawnInterval{1.5f},
		mSwitchInterval{5.f},
		mSpawnDistanceToEdge{100.f},
		mLeftSpawnLocation{0.0f, 0.0f},
		mRightSpawnLocation{0.0f, 0.0f},
		mSpawnLocation{0.0f, 0.0f},
		mRowsToSpawn{4},
		mCurrentRowVanguardCount{0},
		mVanguardsPerRow{5},
		mRowsSpawnCount{0}
	{
	}

	void VanguardStage::StartStage()
	{
		auto windowSize = GetWorld()->GetWindowSize();
		mLeftSpawnLocation = sf::Vector2f{ mSpawnDistanceToEdge, -100.f };
		mRightSpawnLocation = sf::Vector2f{windowSize.x - mSpawnDistanceToEdge, -100.f };

		SwitchRow();
	}

	void VanguardStage::SwitchRow()
	{
		if (mRowsSpawnCount == mRowsToSpawn)
		{
			FinishStage();
			return;
		}

		if (mSpawnLocation == mLeftSpawnLocation)
			mSpawnLocation = mRightSpawnLocation;
		else
			mSpawnLocation = mLeftSpawnLocation;

		mSpawnTimerHandle = TimeManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVanguard, mSpawnInterval, true);

		++mRowsSpawnCount;
	}

	void VanguardStage::StageFinished()
	{
		TimeManager::Get().ClearTimer(mSpawnTimerHandle);
		TimeManager::Get().ClearTimer(mSwitchTimerHandle);
	}

	void VanguardStage::SpawnVanguard()
	{
		weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
		newVanguard.lock()->SetActorLocation(mSpawnLocation);
		++mCurrentRowVanguardCount;

		if (mCurrentRowVanguardCount == mVanguardsPerRow)
		{
			TimeManager::Get().ClearTimer(mSpawnTimerHandle);
			mSwitchTimerHandle = TimeManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwitchRow, mSwitchInterval, false);
			mCurrentRowVanguardCount = 0;
		}
	}
}