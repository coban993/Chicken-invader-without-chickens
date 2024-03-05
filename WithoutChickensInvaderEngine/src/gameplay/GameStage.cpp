#include "gameplay\GameStage.h"
#include "framework\Core.h"

namespace wci
{
	GameStage::GameStage(World* world)
		:mWorld{world},
		mStageFinished{false}
	{
	}

	void GameStage::StartStage()
	{
		LOG("stage started");
	}

	void GameStage::TickStage(float deltaTime)
	{
		
	}

	void GameStage::FinishStage()
	{
		onStageFinished.Broadcast();
		mStageFinished = true;
		StageFinished();
	}

	void GameStage::StageFinished()
	{
		LOG("stage finished");
	}
}