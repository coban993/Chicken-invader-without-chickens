#include "player\PlayerSpaceship.h"
#include <SFML\System.hpp>

namespace wci
{
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
		:Spaceship{owningWorld, path},
		mMoveInput{},
		mSpeed{200.f}
	{
	}

	void PlayerSpaceship::Tick(float delatTime)
	{
		Spaceship::Tick(delatTime);
		HandleInput();
		ConsumeInput(delatTime);
	}

	void PlayerSpaceship::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			mMoveInput.y = -1.f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			mMoveInput.y = 1.f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			mMoveInput.x = -1.f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			mMoveInput.x = 1.f;
	}

	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		SetVelocity(mMoveInput * mSpeed);
		mMoveInput.x = mMoveInput.y = 0.f;
	}
}