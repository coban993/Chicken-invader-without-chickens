#include "weapon\BulletShooter.h"
#include "framework\Core.h"
#include "weapon\Bullet.h"
#include "framework\World.h"

namespace wci
{
	BulletShooter::BulletShooter(Actor* owner, float coolDownTime, const sf::Vector2f localPositionOffset, float localRotationOffset)
		:Shooter{ owner },
		mCooldownClock{},
		mCooldownTime{ coolDownTime },
		mLocalPositionOffset{localPositionOffset},
		mLocalRotationOffset{localRotationOffset}
	{
	}

	bool BulletShooter::IsOnCooldown() const
	{
		if (mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime)
			return false;

		return true;
	}

	void BulletShooter::ShootImpl()
	{
		sf::Vector2f ownerForwardDirection = GetOwner()->GetActorForwardDirection();
		sf::Vector2f ownerRightDirection = GetOwner()->GetActorRightDirection();

		mCooldownClock.restart();
		weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForwardDirection * mLocalPositionOffset.x + ownerRightDirection * mLocalPositionOffset.y);
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + mLocalRotationOffset);
	}
}