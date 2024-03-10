#include "weapon\BulletShooter.h"
#include "framework\Core.h"
#include "weapon\Bullet.h"
#include "framework\World.h"

namespace wci
{
	BulletShooter::BulletShooter(Actor* owner, float coolDownTime, const sf::Vector2f localPositionOffset, float localRotationOffset, const std::string& bulletTexturePath)
		:Shooter{ owner },
		mCooldownClock{},
		mCooldownTime{ coolDownTime },
		mLocalPositionOffset{ localPositionOffset },
		mLocalRotationOffset{ localRotationOffset },
		mBulletTexturePath{bulletTexturePath}
	{
	}

	bool BulletShooter::IsOnCooldown() const
	{
		if (mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime)
			return false;

		return true;
	}

	void BulletShooter::SetBulletTexturePath(const std::string& bulletTexturePath)
	{
		mBulletTexturePath = bulletTexturePath;
	}

	void BulletShooter::ShootImpl()
	{
		sf::Vector2f ownerForwardDirection = GetOwner()->GetActorForwardDirection();
		sf::Vector2f ownerRightDirection = GetOwner()->GetActorRightDirection();

		mCooldownClock.restart();
		weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), mBulletTexturePath);
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForwardDirection * mLocalPositionOffset.x + ownerRightDirection * mLocalPositionOffset.y);
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + mLocalRotationOffset);
	}
}