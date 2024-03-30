#include "framework\BackdropActor.h"
#include "framework\World.h"

namespace wci
{
	BackdropActor::BackdropActor(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		:Actor{owningWorld, texturePath},
		mMovingVelocity{velocity},
		mLeftShift{0},
		mTopShift{0}
	{
		auto windowSize = owningWorld->GetWindowSize();
		GetSprite().setOrigin(0.f, 0.f);
		GetSprite().setTextureRect(sf::IntRect{ sf::Vector2i{0,0}, sf::Vector2i{(int)windowSize.x, (int)windowSize.y} });
		SetTextureRepeated(true);
	}

	void BackdropActor::Tick(float delatTime)
	{
		Actor::Tick(delatTime);

		mLeftShift += delatTime * mMovingVelocity.x;
		mTopShift += delatTime * mMovingVelocity.y;

		sf::IntRect currentRec = GetSprite().getTextureRect();
		currentRec.left = mLeftShift;
		currentRec.top = mTopShift;

		GetSprite().setTextureRect(currentRec);
	}
}