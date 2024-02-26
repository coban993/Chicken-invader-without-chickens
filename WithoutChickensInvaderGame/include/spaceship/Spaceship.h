#pragma once
#include "framework\Actor.h"

namespace wci
{
	class Spaceship : public Actor
	{
	public:
		Spaceship(World* owningWorld, const std::string& texturePath = "");
		virtual void Tick(float delataTime) override;

		void SetVelocity(const sf::Vector2f& newVelocity);
		sf::Vector2f GetVelocity() const { return mVelocity; }

	private:
		sf::Vector2f mVelocity;
	};
}