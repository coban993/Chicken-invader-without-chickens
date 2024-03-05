#pragma once
#include "enemy\EnemySpaceship.h"

namespace wci
{
	class BulletShooter;
	class Vanguard : public EnemySpaceship
	{
	public:
		Vanguard(World* owningWorld, const std::string& textuePath = "SpaceShooterRedux/PNG/Enemies/enemyBlue2.png", const sf::Vector2f& velocity = {0.f, 150.f});

		virtual void Tick(float deltaTime) override;

	private:
		virtual void Shoot() override;

		unique<BulletShooter> mShooter;
 	};
}