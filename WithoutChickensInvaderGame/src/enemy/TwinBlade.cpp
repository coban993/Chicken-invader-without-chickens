#include "enemy\TwinBlade.h"
#include "weapon\BulletShooter.h"

namespace wci
{
	TwinBlade::TwinBlade(World* owningWorld, const std::string& textuePath, const sf::Vector2f& velocity)
		:EnemySpaceship{owningWorld, textuePath},
		mShooterLeft{ new BulletShooter{this, 1.f, {-40.f, -20.f}, 180.f} },
		mShooterRight{ new BulletShooter{this, 1.f, {-40.f, 20.f}, 180.f} }
	{
		SetVelocity(velocity);
	}

	void TwinBlade::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}

	void TwinBlade::Shoot()
	{
		mShooterLeft->Shoot();
		mShooterRight->Shoot();
	}
}