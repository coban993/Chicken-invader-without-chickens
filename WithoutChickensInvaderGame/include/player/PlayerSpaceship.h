#pragma once
#include "spaceship\Spaceship.h"

namespace wci
{
	class BulletShooter;
	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_green.png");

		virtual void Tick(float delatTime) override;
		void SetSpeed(float newSpeed) { mSpeed = newSpeed; }
		float GetSpeed() const { return mSpeed; }

		virtual void Shoot() override;

	private:
		void HandleInput();
		void ConsumeInput(float deltaTime);
		void NormalizeInput();
		void ClampInputOnEdge();

		sf::Vector2f mMoveInput;
		float mSpeed;

		unique<BulletShooter> mShooter;
	};
}