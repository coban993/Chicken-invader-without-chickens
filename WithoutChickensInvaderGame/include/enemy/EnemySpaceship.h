#pragma once
#include "spaceship\Spaceship.h"
#include "player\Reward.h"

namespace wci
{
	class EnemySpaceship : public Spaceship
	{
	public:
		EnemySpaceship(World* owningWorld,
			const std::string& texturePath,
			float collisionDamage = 200.f,
			float rewardSpawnRate = 0.5f,
			const List<RewardFactoryFunc> rewards =
			{
				CreateHealthReward,
				CreateThreeWayShooterReward,
				CreateFrontalWiperReward,
				CreateLifeReward
			}
		);

		virtual void Tick(float deltaTime) override;
		void SetScoreAwardAmount(unsigned int amt);

	private:
		void SpawnReward();

		virtual void OnActorBeingOverlap(Actor* other) override;
		virtual void Blew();

		float mRewardSpawnRate;
		float mCollisionDamage;
		unsigned int mScoreAwardAmount;
		List<RewardFactoryFunc> mRewardsFactories;
	};
}