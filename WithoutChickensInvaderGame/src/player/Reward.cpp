#include "player\PlayerSpaceship.h"
#include "player\Reward.h"
#include "weapon\ThreeWayShooter.h"
#include "weapon\FrontalWiper.h"
#include "framework\World.h"
#include "player\PlayerManager.h"

namespace wci
{
	Reward::Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, float speed)
		:Actor{world, texturePath},
		mRewardFunc{rewardFunc},
		mSpeed{speed}
	{
	}

	void Reward::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}

	void Reward::Tick(float deltaTIme)
	{
		Actor::Tick(deltaTIme);
		AddActorLocationOffset({ 0.f, mSpeed * deltaTIme });
	}

	void Reward::OnActorBeingOverlap(Actor* otherActor)
	{
		if (!otherActor || otherActor->IsPendingDestroyed()) return;

		if (!PlayerManager::Get().GetPlayer()) return;

		weak<PlayerSpaceship> playerSpaceship = PlayerManager::Get().GetPlayer()->GetCurrentSpaceship();

		if (playerSpaceship.expired() || playerSpaceship.lock()->IsPendingDestroyed()) return;

		if (playerSpaceship.lock()->GetUniqueID() == otherActor->GetUniqueID())
		{
			mRewardFunc(playerSpaceship.lock().get());
			Destroy();
		}
	}

	weak<Reward> CreateHealthReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/pill_green.png", RewardHealth);
	}

	weak<Reward> CreateThreeWayShooterReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/powerupRed_bolt.png", RewardThreeWayShooter);
	}

	weak<Reward> CreateFrontalWiperReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/powerupGreen_bolt.png", RewardFrontalWiper);
	}

	weak<Reward> CreateLifeReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/UI/playerLife2_green.png", RewardLife);
	}

	weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc)
	{
		weak<Reward> reward = world->SpawnActor<Reward>(texturePath, rewardFunc);

		return reward;
	}

	void RewardHealth(PlayerSpaceship* player)
	{
		static float rewardAmount = 10.f;

		if (player && !player->IsPendingDestroyed())
			player->GetHealthComponent().ChangeHealth(rewardAmount);
	}
	
	void RewardThreeWayShooter(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroyed())
			player->SetShooter(unique<Shooter>{new ThreeWayShooter{ player, 0.4f, {50.f, 0.f} }});
	}

	void RewardFrontalWiper(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroyed())
			player->SetShooter(unique<Shooter>{new FrontalWiper{ player, 0.4f, {50.f, 0.f} }});
	}

	void RewardLife(PlayerSpaceship* player)
	{
		if (!PlayerManager::Get().GetPlayer()) return;

		PlayerManager::Get().GetPlayer()->AddLifeCount(1);
	}
}