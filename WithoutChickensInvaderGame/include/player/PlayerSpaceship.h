#pragma once
#include "spaceship\Spaceship.h"
#include "framework\TimerManager.h"

namespace wci
{
	class Shooter;
	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip2_green.png");

		virtual void Tick(float delatTime) override;
		void SetSpeed(float newSpeed) { mSpeed = newSpeed; }
		float GetSpeed() const { return mSpeed; }

		virtual void Shoot() override;
		virtual void ApplyDamage(float amt) override;
		virtual void BeginPlay() override;
		void SetShooter(unique<Shooter>&& newShooter);

	private:
		void HandleInput();
		void ConsumeInput(float deltaTime);
		void NormalizeInput();
		void ClampInputOnEdge();
		void StopInvulnerable();
		void UpdateInvulnerable(float deltaTime);

		sf::Vector2f mMoveInput;
		float mSpeed;

		unique<Shooter> mShooter;

		float mInvulnerableTime;
		TimerHandle mInvulnerableTimerHandle;
		bool mInvulnerable;
		float mInvulnerableFlashInterval;
		float mInvulnerableFlashTimer;
		float mInvulnerableFlashDir;
	};
}