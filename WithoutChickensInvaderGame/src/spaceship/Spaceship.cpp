#pragma once
#include "spaceship\Spaceship.h"

namespace wci
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		:Actor{owningWorld, texturePath},
		mVelocity{}
	{
	}

	void Spaceship::Tick(float delataTime)
	{
		Actor::Tick(delataTime);
		AddActorLocationOffset(GetVelocity() * delataTime);
	}

	void Spaceship::SetVelocity(const sf::Vector2f& newVelocity)
	{
		mVelocity = newVelocity;
	}
}