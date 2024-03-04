#pragma once
#include <SFML\Graphics.hpp>
#include "Core.h"
#include "framework\Object.h"

namespace wci
{
	class Actor;
	class Application;
	class World : public Object
	{
	public:
		World(Application* owningApp); 
		virtual ~World();

		void TickInternal(float deltaTime);
		void BeginPlayingInternal();
		void Render(sf::RenderWindow& window);

		template<typename ActorType, typename... Args>
		weak<ActorType> SpawnActor(Args... args);

		sf::Vector2u GetWindowSize() const;

		void CleanCycle();

	private:
		Application* mOwningApp;
		bool mBeginPlay;

		virtual void BeginPLay();
		virtual void Tick(float deltaTime);

		List<shared<Actor>> mActors;
		List<shared<Actor>> mPendingActors;
	};

	template<typename ActorType, typename... Args>
	weak<ActorType> World::SpawnActor(Args... args)
	{
		shared<ActorType> newActor{ new ActorType{this, args...} };
		mPendingActors.push_back(newActor);
		return newActor;
	}
}