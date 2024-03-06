#pragma once
#include <SFML\System.hpp>
#include "weapon\Shooter.h"

namespace wci
{
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, float coolDownTime = 1.f, const sf::Vector2f localPositionOffset = {0.0f, 0.0f}, float localRotationOffset = 0.f);

		virtual bool IsOnCooldown() const override;

	private:
		virtual void ShootImpl() override;

		sf::Clock mCooldownClock;
		float mCooldownTime;

		sf::Vector2f mLocalPositionOffset;
		float mLocalRotationOffset;
	};
}