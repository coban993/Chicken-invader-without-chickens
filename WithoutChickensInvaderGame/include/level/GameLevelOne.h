#pragma once
#include "framework\World.h"
#include "framework\TimerManager.h"

namespace wci
{
	class PlayerSpaceship;
	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owningApp);

	private:
		void TimerCallback_Test();
		virtual void BeginPLay() override;

		weak<PlayerSpaceship> testPlayerSpaceship;
		TimerHandle timerHandle_test;
	};
}