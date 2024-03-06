#include "framework\TimerManager.h"
#include "gameplay\WaitStage.h"

namespace wci
{
	WaitStage::WaitStage(World* world, float waitDuration)
		:GameStage{world},
		mWaitDuration{waitDuration}
	{
	}

	void WaitStage::StartStage()
	{
		TimeManager::Get().SetTimer(GetWeakRef(), &WaitStage::FinishStage, mWaitDuration);
	}
}