#pragma once
#include "spaceship\Spaceship.h"

namespace wci
{
	class EnemySpaceship : public Spaceship
	{
	public:
		EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage = 200.f);

		virtual void Tick(float deltaTime) override;

	private:
		virtual void OnActorBeingOverlap(Actor* other) override;

		float mCollisionDamage;
	};
}