#pragma once
#include "gameplay\GameStage.h"

namespace wci
{
	class WaitStage : public GameStage
	{
	public:
		WaitStage(World* world, float waitDuration = 5.f);

		virtual void StartStage() override;

	private:
		float mWaitDuration;
	};
}