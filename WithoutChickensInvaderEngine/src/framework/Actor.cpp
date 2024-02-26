#include "framework\Actor.h"
#include "framework\Core.h"
#include "framework\AssetManager.h"
#include "framework\MathUtility.h"

namespace wci
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		:mOwningWorld{owningWorld},
		mHasBeginPlay{false},
		mSprite{},
		mTexture{}
	{
		SetTexture(texturePath);
	}

	Actor::~Actor()
	{
		LOG("actor is destroyed");
	}

	void Actor::BeginPlayInternal()
	{
		if (!mHasBeginPlay)
		{
			mHasBeginPlay = true;
			BeginPlay();
		}
	}

	void Actor::BeginPlay()
	{
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (!IsPendingDestroyed())
			Tick(deltaTime);
	}

	void Actor::Tick(float deltaTime)
	{
	}

	void Actor::SetTexture(const std::string& texturePath)
	{
		mTexture = AssetManager::Get().LoadTexture(texturePath);
		if (!mTexture) return;

		mSprite.setTexture(*mTexture);
		
		int textureWidth = mTexture->getSize().x;
		int textureHeight = mTexture->getSize().y;

		mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{},
			sf::Vector2i{textureWidth, textureHeight} });
		CenterPivot();
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroyed())
			return;

		window.draw(mSprite);
	}

	void Actor::SetActorLocation(const sf::Vector2f& newLocation)
	{
		mSprite.setPosition(newLocation);
	}

	void Actor::SetActorRotation(float newRotation)
	{
		mSprite.setRotation(newRotation);
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offset)
	{
		SetActorLocation(GetActorLocation() + offset);
	}

	void Actor::AddActorRotationOffset(float offset)
	{
		SetActorRotation(GetActorRotation() + offset);
	}

	sf::Vector2f Actor::GetActorLocation() const
	{
		return mSprite.getPosition();
	}

	float Actor::GetActorRotation() const
	{
		return mSprite.getRotation();
	}

	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation());
	}

	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return RotationToVector(GetActorRotation() + 90.f);
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bound = mSprite.getGlobalBounds();
		mSprite.setOrigin(bound.width/2.f, bound.height/2.f);
	}
}