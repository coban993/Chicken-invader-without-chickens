#pragma once
#include "spaceship\Spaceship.h"

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

		void SetShooter(unique<Shooter>&& newShooter);

	private:
		void HandleInput();
		void ConsumeInput(float deltaTime);
		void NormalizeInput();
		void ClampInputOnEdge();

		sf::Vector2f mMoveInput;
		float mSpeed;

		unique<Shooter> mShooter;
	};
}