#include "enemy\EnemySpaceship.h"

namespace wci
{
	EnemySpaceship::EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage)
		:Spaceship{owningWorld, texturePath},
		mCollisionDamage{collisionDamage}
	{
		SetTeamID(2);
	}

	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);

		if (IsActorOutOfBounds(GetActorGlobalBounds().width * 2.f))
			Destroy();
	}

	void EnemySpaceship::OnActorBeingOverlap(Actor* other)
	{
		Spaceship::OnActorBeingOverlap(other);

		if (IsOtherHostile(other))
			other->ApplyDamage(mCollisionDamage);
	}
}