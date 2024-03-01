#pragma once
#include "spaceship\Spaceship.h"

namespace wci
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		:Actor{ owningWorld, texturePath },
		mVelocity{},
		mHealth{100, 100}
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

	void Spaceship::Shoot()
	{
	}
	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);

		mHealth.onHealthChange.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
		mHealth.onTakenDamage.BindAction(GetWeakRef(), &Spaceship::OnTakenDamage);
		mHealth.onHealthEmpty.BindAction(GetWeakRef(), &Spaceship::Blow);
	}

	void Spaceship::ApplyDamage(float amount)
	{
		mHealth.ChangeHealth(-amount);
	}

	void Spaceship::OnHealthChanged(float amount, float health, float maxHealth)
	{
		
	}

	void Spaceship::OnTakenDamage(float amount, float health, float maxHealth)
	{

	}

	void Spaceship::Blow()
	{
		Destroy();
	}
}