#pragma once
#include <box2d\b2_world.h>
#include "Core.h"

namespace wci
{
	class Actor;
	class PhysicsContactListener : public b2ContactListener
	{
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;
	};

	class Physics
	{
	public:
		static Physics& Get();
		void Step(float deltaTime);
		b2Body* AddListener(Actor* listener);
		float GetPhysicsScale() const { return mPhycisScale; }

		void RemoveListener(b2Body* bodyToRemove);
		static void Cleanup();

	protected:
		Physics();

	private:
		void ProcessPendingRemoveListeners();

		static unique<Physics> physics;
		b2World mPhysicsWorld;
		float mPhycisScale;
		int mVelocityIteration;
		int mPositionIteration;
		PhysicsContactListener mContactListener;

		Set<b2Body*> mPendingRemoveListener;
	};
}