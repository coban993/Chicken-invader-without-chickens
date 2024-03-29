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
		virtual void BeginPlay() override;

	private:
		void CheckMove();

		float mSpeed;
		float mBaseSpeed;
		float mSwitchDistanceToEdge;

		BulletShooter mBaseShooterLeft;
		BulletShooter mBaseShooterRight;
		ThreeWayShooter mThreeWayShooter;
		FrontalWiper mFrontalWiperLeft;
		FrontalWiper mFrontalWiperRight;
		BulletShooter mFinalStageShooterLeft;
		BulletShooter mFinalStageShooterRight;

		void ShootBaseShooters();
		void ShootThreeWayShooter();
		void ShootFrontalWiperShooters();

		void HealthChanged(float amt, float currentHealth, float maxHealth);

		int mStage;
		void SetStage(int newStage);
	};
}