#pragma once
#include <SFML\Graphics.hpp>
#include "Object.h"
#include "Core.h"

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
		void Render(sf::RenderWindow& window);

		void SetActorLocation(const sf::Vector2f& newLocation);
		void SetActorRotation(float newRotation);
		void AddActorLocationOffset(const sf::Vector2f& offset);
		void AddActorRotationOffset(float offset);

		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const;

		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;

	private:
		void CenterPivot();

		World* mOwningWorld;
		bool mHasBeginPlay;

		sf::Sprite mSprite;
		shared<sf::Texture> mTexture;
	};
}