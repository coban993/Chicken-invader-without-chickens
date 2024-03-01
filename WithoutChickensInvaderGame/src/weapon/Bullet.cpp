#include "weapon\Bullet.h"

namespace wci
{
	Bullet::Bullet(World* world, Actor* owner, const std::string& texturePath, float speed, float damage)
		:Actor{world, texturePath},
		mOwner{owner},
		mSpeed{speed},
		mDamage{damage}
	{
		SetTeamID(owner->GetTeamID());
	}

	void Bullet::SetSpeed(float newSpeed)
	{
		mSpeed = newSpeed;
	}

	void Bullet::SetDamage(float newDamage)
	{
		mDamage = newDamage;
	}

	void Bullet::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		Move(deltaTime);
		if (IsActorOutOfBounds())
			Destroy();
	}

	void Bullet::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}

	void Bullet::Move(float deltaTime)
	{
		AddActorLocationOffset(GetActorForwardDirection() * mSpeed * deltaTime);
	}

	void Bullet::OnActorBeingOverlap(Actor* other)
	{
		if (IsOtherHostile(other))
		{
			other->ApplyDamage(GetDamage());
			Destroy();
		}
	}
}