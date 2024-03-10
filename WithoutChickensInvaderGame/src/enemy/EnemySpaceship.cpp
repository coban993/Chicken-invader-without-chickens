#include "enemy\EnemySpaceship.h"
#include "framework\MathUtility.h"

namespace wci
{
	EnemySpaceship::EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage, const List<RewardFactoryFunc> rewards)
		:Spaceship{ owningWorld, texturePath },
		mCollisionDamage{ collisionDamage },
		mRewardsFactories{rewards}
	{
		SetTeamID(2);
	}

	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);

		if (IsActorOutOfBounds(GetActorGlobalBounds().width * 2.f))
			Destroy();
	}

	void EnemySpaceship::SpawnReward()
	{
		if (mRewardsFactories.size() == 0) return;

		int pick = (int)RandomRange(0, mRewardsFactories.size());

		if (pick >= 0 && pick < mRewardsFactories.size())
		{
			weak<Reward> newReward = mRewardsFactories[pick](GetWorld());
			newReward.lock()->SetActorLocation(GetActorLocation());
		}
	}

	void EnemySpaceship::OnActorBeingOverlap(Actor* other)
	{
		Spaceship::OnActorBeingOverlap(other);

		if (IsOtherHostile(other))
			other->ApplyDamage(mCollisionDamage);
	}

	void EnemySpaceship::Blew()
	{
		SpawnReward();
	}
}