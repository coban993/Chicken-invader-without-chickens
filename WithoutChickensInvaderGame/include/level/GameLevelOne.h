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
		virtual void BeginPLay() override;
		virtual void InitGameStages();

		weak<PlayerSpaceship> testPlayerSpaceship;
		TimerHandle timerHandle_test;
	};
}