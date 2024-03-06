#pragma once
#include <SFML\Graphics.hpp>
#include "framework\TimerManager.h"
#include "gameplay\GameStage.h"

namespace wci
{
	class HexagonStage : public GameStage
	{
	public:
		HexagonStage(World* world);

		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;
		void SpawnHexagon();

		float mSpawnInterval;
		float mSideSpawnOffset;
		int mSpawnGroupAmount;
		int mCurrentSpawnCount;

		sf::Vector2f mRightSpawnLocation;
		sf::Vector2f mLeftSpawnLocation;
		sf::Vector2f mMidSpawnLocation;

		TimerHandle mSpawnTimer;
	};
}