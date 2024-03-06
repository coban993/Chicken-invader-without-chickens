#pragma once
#include <SFML\Graphics.hpp>
#include "gameplay\GameStage.h"
#include "framework\TimerManager.h"

namespace wci
{
	class TwinBladeStage : public GameStage
	{
	public:
		TwinBladeStage(World* world);

		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;

		void SpawnTwinBlade();

		float mSpawnInterval;
		float mSpawnDistanceToCenter;

		sf::Vector2f mLeftSpawnLocation;
		sf::Vector2f mRightSpawnLocation;
		sf::Vector2f mSpawnLocation;

		TimerHandle mSpawnTimerHandle;

		int mSpawnAmount;
		int mCurrentSpawnCount;
	};
}