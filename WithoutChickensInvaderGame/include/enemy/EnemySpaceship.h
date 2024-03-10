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
			const List<RewardFactoryFunc> rewards =
			{
				CreateHealthReward,
				CreateThreeWayShooterReward,
				CreateFrontalWiperReward
			}
		);

		virtual void Tick(float deltaTime) override;

	private:
		void SpawnReward();

		virtual void OnActorBeingOverlap(Actor* other) override;
		virtual void Blew();

		float mCollisionDamage;
		List<RewardFactoryFunc> mRewardsFactories;
	};
}