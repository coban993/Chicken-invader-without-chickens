#pragma once
#include "enemy\EnemySpaceship.h"
#include "weapon\BulletShooter.h"
#include "weapon\ThreeWayShooter.h"
#include "weapon\FrontalWiper.h"

namespace wci
{
	class Boss : public EnemySpaceship
	{
	public:
		Boss(World* world);

		virtual void Tick(float deltaTime) override;

	private:
		void CheckMove();

		float mSpeed;
		float mSwitchDistanceToEdge;

		BulletShooter mBaseShooterLeft;
		BulletShooter mBaseShooterRight;
		void ShootBaseShooters();
	};
}