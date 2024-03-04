#include "enemy\Vanguard.h"
#include "weapon\BulletShooter.h"

namespace wci
{
	Vanguard::Vanguard(World* owningWorld, const std::string& textuePath, const sf::Vector2f& velocity)
		:EnemySpaceship{owningWorld, textuePath},
		mShooter{ new BulletShooter{this} }
	{
		SetVelocity(velocity);
		SetActorRotation(180.f);
	}

	void Vanguard::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}

	void Vanguard::Shoot()
	{
		mShooter->Shoot();
	}
}