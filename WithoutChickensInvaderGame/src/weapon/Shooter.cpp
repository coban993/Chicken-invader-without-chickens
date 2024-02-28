#include "weapon\Shooter.h"

namespace wci
{
	Shooter::Shooter(Actor* owner)
		:mOwner{owner}
	{

	}

	void Shooter::Shoot()
	{
		if (CanShoot() && !IsOnCooldown())
			ShootImpl();
	}

}