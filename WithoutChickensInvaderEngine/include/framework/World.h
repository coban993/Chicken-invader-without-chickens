#pragma once
#include <SFML\Graphics.hpp>
#include "Core.h"
#include "framework\Object.h"

namespace wci
{
	class Actor;
	class Application;
	class HUD;
	class GameStage;
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

		template<typename HUDType, typename... Args>
		weak<HUDType> SpawnHUD(Args... args);

		sf::Vector2u GetWindowSize() const;

		void CleanCycle();
		void AddStage(const shared<GameStage>& newStage);

		bool DispatchEvent(const sf::Event& event);

		Application* GetApplication() { return mOwningApp; }
		const Application* GetApplication() const { return mOwningApp; }

	private:
		Application* mOwningApp;
		bool mBeginPlay;

		virtual void BeginPLay();
		virtual void Tick(float deltaTime);

		void RenderHUD(sf::RenderWindow& window);

		List<shared<Actor>> mActors;
		List<shared<Actor>> mPendingActors;
		List<shared<GameStage>> mGameStages;
		List<shared<GameStage>>::iterator mCurrentStage;

		shared<HUD> mHUD;

		virtual void InitGameStages();
		virtual void AllGameStagesFinished();

		void NextGameStage();
		void StartStages();
	};

	template<typename ActorType, typename... Args>
	weak<ActorType> World::SpawnActor(Args... args)
	{
		shared<ActorType> newActor{ new ActorType{this, args...} };
		mPendingActors.push_back(newActor);
		return newActor;
	}

	template<typename HUDType, typename ...Args>
	inline weak<HUDType> World::SpawnHUD(Args ...args)
	{
		shared<HUDType> newHUD{ new HUDType(args...)};
		mHUD = newHUD;
		return newHUD;
	}
}