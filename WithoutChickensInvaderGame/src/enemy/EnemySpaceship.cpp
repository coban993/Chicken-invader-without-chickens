#include "enemy\EnemySpaceship.h"
#include "framework\MathUtility.h"
#include "player\PlayerManager.h"

namespace wci
{
	EnemySpaceship::EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage, float rewardSpawnRate, const List<RewardFactoryFunc> rewards)
		:Spaceship{ owningWorld, texturePath },
		mCollisionDamage{ collisionDamage },
		mRewardSpawnRate{rewardSpawnRate},
		mScoreAwardAmount{10},
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

	void EnemySpaceship::SetScoreAwardAmount(unsigned int amt)
	{
		mScoreAwardAmount = amt;
	}

	void EnemySpaceship::SetRewardSpawnRate(float rate)
	{
		if (rate < 0 || rate > 1) return;

		mRewardSpawnRate = rate;
	}

	void EnemySpaceship::SpawnReward()
	{
		if (mRewardsFactories.size() == 0) return;

		if (mRewardSpawnRate < RandomRange(0, 1)) return;

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

		Player* player = PlayerManager::Get().GetPlayer();

		if (player)
			player->AddScore(mScoreAwardAmount);
	}
}