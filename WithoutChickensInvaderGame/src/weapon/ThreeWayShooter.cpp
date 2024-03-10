#include "weapon\ThreeWayShooter.h"

namespace wci
{
	ThreeWayShooter::ThreeWayShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset)
		:Shooter{owner},
		mShooterLeft{owner, cooldownTime, localOffset, -30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		mShooterRight{owner, cooldownTime, localOffset, 30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		mShooterMid{owner, cooldownTime, localOffset, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" }
	{
	}

	void ThreeWayShooter::ShootImpl()
	{
		mShooterLeft.Shoot();
		mShooterRight.Shoot();
		mShooterMid.Shoot();
	}
}