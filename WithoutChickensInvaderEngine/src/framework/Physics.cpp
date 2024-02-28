#include <box2d\b2_body.h>
#include <box2d\b2_polygon_shape.h>
#include <box2d\b2_fixture.h>
#include <box2d\b2_contact.h>
#include "framework\Physics.h"
#include "framework\Actor.h"
#include "framework\MathUtility.h"

namespace wci
{
	unique<Physics> Physics::physics{ nullptr };

	Physics& Physics::Get()
	{
		if (!physics)
			physics = std::move(unique<Physics>{new Physics});

		return *physics;
	}

	Physics::Physics()
		:mPhysicsWorld{ b2Vec2{0.f, 0.0f} },
		mPhycisScale{0.01f},
		mVelocityIteration{8},
		mPositionIteration{3},
		mContactListener{},
		mPendingRemoveListener{}
	{
		mPhysicsWorld.SetContactListener(&mContactListener);
		mPhysicsWorld.SetAllowSleeping(false);
	}

	void Physics::ProcessPendingRemoveListeners()
	{
		for (auto listener : mPendingRemoveListener)
		{
			mPhysicsWorld.DestroyBody(listener);
		}

		mPendingRemoveListener.clear();
	}

	void Physics::Step(float deltaTime)
	{
		ProcessPendingRemoveListeners();
		mPhysicsWorld.Step(deltaTime, mVelocityIteration, mPositionIteration);
	}

	b2Body* Physics::AddListener(Actor* listener)
	{
		if (listener->IsPendingDestroyed())
			return nullptr;

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);
		bodyDef.position.Set(listener->GetActorLocation().x * GetPhysicsScale(),
			listener->GetActorLocation().y * GetPhysicsScale());
		bodyDef.angle = DegreesToRadians(listener->GetActorRotation());

		b2Body* body = mPhysicsWorld.CreateBody(&bodyDef);

		b2PolygonShape shape;
		auto bound = listener->GetActorGlobalBounds();
		shape.SetAsBox(bound.width / 2.f * GetPhysicsScale(),
			bound.height / 2.f * GetPhysicsScale());

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.isSensor = true;

		body->CreateFixture(&fixtureDef);

		return body;
	}

	void Physics::RemoveListener(b2Body* bodyToRemove)
	{
		mPendingRemoveListener.insert(bodyToRemove);
	}

	void Physics::Cleanup()
	{
		physics = std::move(unique<Physics>{new Physics});
	}

	void PhysicsContactListener::BeginContact(b2Contact* contact)
	{
		Actor* ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		Actor* ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (ActorA && !ActorA->IsPendingDestroyed())
			ActorA->OnActorBeingOverlap(ActorB);

		if (ActorB && !ActorB->IsPendingDestroyed())
			ActorB->OnActorBeingOverlap(ActorA);
	}

	void PhysicsContactListener::EndContact(b2Contact* contact)
	{
		Actor* ActorA = nullptr;
		Actor* ActorB = nullptr;

		if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
			ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);

		if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
			ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (ActorA && !ActorA->IsPendingDestroyed())
			ActorA->OnActorEndOverlap(ActorB);

		if (ActorB && !ActorB->IsPendingDestroyed())
			ActorB->OnActorEndOverlap(ActorA);
	}
}