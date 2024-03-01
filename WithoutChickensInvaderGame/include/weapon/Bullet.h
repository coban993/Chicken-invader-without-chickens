#pragma once
#include "framework\Actor.h"

namespace wci
{
	class Bullet : public Actor
	{
	public:
		Bullet(World* world, Actor* owner, const std::string& texturePath, float speed = 600.f, float damage = 10.f);

		float GetDamage() const { return mDamage; }

		void SetSpeed(float newSpeed);
		void SetDamage(float newDamage);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;

	private:
		void Move(float deltaTime);
		virtual void OnActorBeingOverlap(Actor* other) override;

		Actor* mOwner;
		float mSpeed;
		float mDamage;
	};
}