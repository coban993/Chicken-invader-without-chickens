#pragma once
#include <SFML\Graphics.hpp>
#include "Object.h"
#include "Core.h"
#include "Delegate.h"

class b2Body;
namespace wci
{
	class World;
	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");
		virtual ~Actor();

		void BeginPlayInternal();
		virtual void BeginPlay();

		void TickInternal(float deltaTime);
		virtual void Tick(float deltaTime);

		void SetTexture(const std::string& texturePath);
		virtual void Render(sf::RenderWindow& window);

		void SetActorLocation(const sf::Vector2f& newLocation);
		void SetActorRotation(float newRotation);
		void AddActorLocationOffset(const sf::Vector2f& offset);
		void AddActorRotationOffset(float offset);

		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const;

		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;
		sf::Vector2u GetWindowSize() const;
		sf::FloatRect GetActorGlobalBounds() const;

		const World* GetWorld() const { return mOwningWorld; }
		World* GetWorld() { return mOwningWorld; }

		bool IsActorOutOfBounds(float allowance = 10.f) const;

		void SetEnablePhysics(bool enable);
		virtual void OnActorBeingOverlap(Actor* other);
		virtual void OnActorEndOverlap(Actor* other);
		virtual void Destroy() override;

		uint8 GetTeamID() const { return mTeamID; }
		static uint8 GetNeturalTeamID() { return neturalTeamID; }

		void SetTeamID(uint8 teamID) { mTeamID = teamID; }

		bool IsOtherHostile(Actor* other) const;

		virtual void ApplyDamage(float amount);

		sf::Sprite& GetSprite() { return mSprite; }
		const sf::Sprite& GetSprite() const { return mSprite; }

		Delegate<Actor*> onActorDestoryed;

		void SetTextureRepeated(bool repeated);

	private:
		void UpdatePhysicsTransform();
		void InitializePhysics();
		void UnInitializePhysics();
		void CenterPivot();

		World* mOwningWorld;
		bool mHasBeginPlay;

		sf::Sprite mSprite;
		shared<sf::Texture> mTexture;
		b2Body* mPhysicBody;

		bool mPhysicsEnabled;
		uint8 mTeamID;

		const static uint8 neturalTeamID = 255;
	};
}