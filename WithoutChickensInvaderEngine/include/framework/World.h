#pragma once
#include "Core.h"
#include <SFML\Graphics.hpp>

namespace wci
{
	class Actor;
	class Application;
	class World
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

		void BeginPLay();
		void Tick(float deltaTime);

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