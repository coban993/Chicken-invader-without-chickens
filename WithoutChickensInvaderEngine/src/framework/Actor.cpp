#include "framework\Actor.h"
#include "framework\Core.h"
#include "framework\AssetManager.h"
#include "framework\MathUtility.h"
#include "framework\World.h"
#include "framework\Physics.h"
#include <box2d\b2_body.h>

namespace wci
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		:mOwningWorld{owningWorld},
		mHasBeginPlay{false},
		mSprite{},
		mTexture{},
		mPhysicBody{nullptr},
		mPhysicsEnabled{false},
		mTeamID{GetNeturalTeamID()}
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
		UpdatePhysicsTransform();
	}

	void Actor::SetActorRotation(float newRotation)
	{
		mSprite.setRotation(newRotation);
		UpdatePhysicsTransform();
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
		return RotationToVector(GetActorRotation() - 90.f);
	}

	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return RotationToVector(GetActorRotation());
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return mOwningWorld->GetWindowSize();
	}

	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return mSprite.getGlobalBounds();
	}

	bool Actor::IsActorOutOfBounds() const
	{
		float windowWidth = GetWorld()->GetWindowSize().x;
		float windowHeight = GetWorld()->GetWindowSize().y;

		float width = GetActorGlobalBounds().width;
		float heaight = GetActorGlobalBounds().height;

		sf::Vector2f actorPosition = GetActorLocation();

		if (actorPosition.x < -width)
			return true;

		if (actorPosition.x > windowWidth + width)
			return true;

		if (actorPosition.y < -heaight)
			return true;

		if (actorPosition.y > windowHeight + heaight)
			return true;

		return false;
	}

	void Actor::SetEnablePhysics(bool enable)
	{
		mPhysicsEnabled = enable;
		if (mPhysicsEnabled)
			InitializePhysics();
		else
			UnInitializePhysics();
	}

	void Actor::OnActorBeingOverlap(Actor* other)
	{
		
	}

	void Actor::OnActorEndOverlap(Actor* other)
	{
		
	}

	void Actor::Destroy()
	{
		UnInitializePhysics();
		Object::Destroy();
	}

	bool Actor::IsOtherHostile(Actor* other) const
	{
		if (GetTeamID() == GetNeturalTeamID() || other->GetTeamID() == GetNeturalTeamID()) return false;
			
		return GetTeamID() != other->GetTeamID();
	}

	void Actor::ApplyDamage(float amount)
	{

	}

	void Actor::UpdatePhysicsTransform()
	{
		if (mPhysicBody)
		{
			float physicsScale = Physics::Get().GetPhysicsScale();
			b2Vec2 position{ GetActorLocation().x * physicsScale,
				GetActorLocation().y * physicsScale };
			float rotation = DegreesToRadians(GetActorRotation());

			mPhysicBody->SetTransform(position, rotation);
		}
	}

	void Actor::InitializePhysics()
	{
		if (!mPhysicBody)
			mPhysicBody = Physics::Get().AddListener(this);
	}

	void Actor::UnInitializePhysics()
	{
		if (mPhysicBody)
			Physics::Get().RemoveListener(mPhysicBody);
		mPhysicBody = nullptr;
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bound = mSprite.getGlobalBounds();
		mSprite.setOrigin(bound.width/2.f, bound.height/2.f);
	}
}