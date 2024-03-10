#pragma once
#include "spaceship\Spaceship.h"
#include "framework\MathUtility.h"
#include "VFX\Explosion.h"

namespace wci
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		:Actor{ owningWorld, texturePath },
		mVelocity{},
		mHealth{100, 100},
		mBlinkTime{0},
		mBlinkDuration{0.2f},
		mBlinkColorOffset{255, 0, 0, 255}
	{
	}

	void Spaceship::Tick(float delataTime)
	{
		Actor::Tick(delataTime);
		AddActorLocationOffset(GetVelocity() * delataTime);
		UpdateBlink(delataTime);
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
		Blink();
	}

	void Spaceship::Blew()
	{
	}

	void Spaceship::Blow()
	{
		Explosion* exp = new Explosion();
		exp->SpawnExplosion(GetWorld(), GetActorLocation());
		Blew();
		Destroy();
		delete exp;
	}

	void Spaceship::Blink()
	{
		if (mBlinkTime == 0.f)
			mBlinkTime = mBlinkDuration;
	}

	void Spaceship::UpdateBlink(float deltaTime)
	{
		if (mBlinkTime > 0)
		{
			mBlinkTime -= deltaTime;
			mBlinkTime = mBlinkTime > 0 ? mBlinkTime : 0.f;

			GetSprite().setColor(LerpColor(sf::Color::White, mBlinkColorOffset, mBlinkTime));
		}
	}
}