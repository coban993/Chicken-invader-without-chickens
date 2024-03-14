#pragma once
#include "framework\World.h"
#include "framework\TimerManager.h"

namespace wci
{
	class GameplayHUD;
	class PlayerSpaceship;
	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owningApp);

	private:
		virtual void BeginPLay() override;
		virtual void InitGameStages();

		void PlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship);
		void GameOver();

		weak<PlayerSpaceship> mPlayerSpaceship;
		weak<GameplayHUD> mGameplayHUD;
		TimerHandle timerHandle_test;
	};
}