#pragma once
#include <SFML\Graphics.hpp>
#include "weapon\BulletShooter.h"

namespace wci
{
	class ThreeWayShooter : public Shooter
	{
	public:
		ThreeWayShooter(Actor* owner, float cooldownTime = 0.3f, const sf::Vector2f& localOffset = {0.f, 0.f});

		BulletShooter mShooterLeft;
		BulletShooter mShooterRight;
		BulletShooter mShooterMid;

		BulletShooter mTopLevelShooterLeft;
		BulletShooter mTopLevelShooterRight;

		virtual void IncrementLevel(int amt = 1) override;

	private:
		virtual void ShootImpl();
	};
}