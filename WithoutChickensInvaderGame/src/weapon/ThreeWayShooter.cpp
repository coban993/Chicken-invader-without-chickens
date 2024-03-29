#include "weapon\ThreeWayShooter.h"

namespace wci
{
	ThreeWayShooter::ThreeWayShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset)
		:Shooter{owner},
		mShooterLeft{owner, cooldownTime, localOffset, -30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		mShooterRight{owner, cooldownTime, localOffset, 30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		mShooterMid{owner, cooldownTime, localOffset, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		mTopLevelShooterLeft{ owner, cooldownTime, localOffset, 15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		mTopLevelShooterRight{ owner, cooldownTime, localOffset, -15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" }
	{
	}

	void ThreeWayShooter::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel();
		mShooterLeft.IncrementLevel(amt);
		mShooterRight.IncrementLevel(amt);
		mShooterMid.IncrementLevel(amt);

		mTopLevelShooterLeft.IncrementLevel(amt);
		mTopLevelShooterRight.IncrementLevel(amt);
	}

	void ThreeWayShooter::SetCurrentLevel(int level)
	{
		Shooter::SetCurrentLevel(level);
		mShooterLeft.SetCurrentLevel(level);
		mShooterRight.SetCurrentLevel(level);
		mShooterMid.SetCurrentLevel(level);

		mTopLevelShooterLeft.SetCurrentLevel(level);
		mTopLevelShooterRight.SetCurrentLevel(level);
	}

	void ThreeWayShooter::ShootImpl()
	{
		mShooterLeft.Shoot();
		mShooterRight.Shoot();
		mShooterMid.Shoot();

		if (GetCurrentLevel() == GetMaxLevel())
		{
			mTopLevelShooterLeft.Shoot();
			mTopLevelShooterRight.Shoot();
		}
	}
}