#pragma once
#include <SFML\Graphics.hpp>
#include "gameplay\GameStage.h"
#include "framework\TimerManager.h"

namespace wci
{
	class UFOStage : public GameStage
	{
	public:
		UFOStage(World* world);

		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;
		sf::Vector2f GetRandomSpawnLocation() const;
		void SpawnUFO();

		float mSpawnInterval;
		float mUFOSpeed;
		int mSpawnAmount;
		int mCurrentSpawnAmount;

		TimerHandle mSpawnTimer;
	};
}