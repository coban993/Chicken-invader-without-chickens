#pragma once
#include <SFML\Graphics.hpp>
#include "gameplay\GameStage.h"
#include "framework\TimerManager.h"

namespace wci
{
	class VanguardStage : public GameStage
	{
	public:
		VanguardStage(World* world);

		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;

		void SpawnVanguard();
		void SwitchRow();

		float mSpawnInterval;
		float mSwitchInterval;
		float mSpawnDistanceToEdge;

		sf::Vector2f mLeftSpawnLocation;
		sf::Vector2f mRightSpawnLocation;
		sf::Vector2f mSpawnLocation;

		TimerHandle mSpawnTimerHandle;
		TimerHandle mSwitchTimerHandle;

		int mRowsToSpawn;
		int mRowsSpawnCount;

		int mVanguardsPerRow;
		int mCurrentRowVanguardCount;
	};
}