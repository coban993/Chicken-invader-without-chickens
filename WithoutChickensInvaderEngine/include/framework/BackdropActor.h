#pragma once
#include "framework\Actor.h"

namespace wci
{
	class BackdropActor : public Actor
	{
	public:
		BackdropActor(World* owningWorld,
			const std::string& texturePath,
			const sf::Vector2f& velocity = {0.f, -50.f}
		);

		virtual void Tick(float delatTime) override;

	private:
		sf::Vector2f mMovingVelocity;
		float mLeftShift;
		float mTopShift;
	};
}