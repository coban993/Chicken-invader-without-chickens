#pragma once
#include "framework\Actor.h"
#include "gameplay\HelathComponent.h"

namespace wci
{
	class Spaceship : public Actor
	{
	public:
		Spaceship(World* owningWorld, const std::string& texturePath = "");
		virtual void Tick(float delataTime) override;

		void SetVelocity(const sf::Vector2f& newVelocity);
		sf::Vector2f GetVelocity() const { return mVelocity; }

		virtual void Shoot();
		virtual void BeginPlay() override;
		virtual void ApplyDamage(float amount) override;

		HealthComponent& GetHealthComponent() { return mHealth; }

	private:
		virtual void OnHealthChanged(float amount, float health, float maxHealth);
		virtual void OnTakenDamage(float amount, float health, float maxHealth);
		virtual void Blew();

		void Blow();
		void Blink();
		void UpdateBlink(float deltaTime);

		sf::Vector2f mVelocity;
		HealthComponent mHealth;

		sf::Color mBlinkColorOffset;
		float mBlinkDuration;
		float mBlinkTime;
	};
}