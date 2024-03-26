#include "framework\World.h"
#include "framework\Core.h"
#include "framework\Actor.h"
#include "framework\Application.h"
#include "gameplay\GameStage.h"
#include "widgets\HUD.h"

namespace wci
{
	World::World(Application* owningApp)
		:mOwningApp{ owningApp },
		mBeginPlay{false},
		mActors{},
		mPendingActors{},
		mGameStages{},
		mCurrentStage{mGameStages.end()}
	{
	}

	World::~World()
	{
	}

	void World::TickInternal(float deltaTime)
	{
		for (shared<Actor> actor : mPendingActors)
		{
			mActors.push_back(actor);
			actor->BeginPlayInternal();
		}

		mPendingActors.clear();
		for (auto iter = mActors.begin(); iter != mActors.end();)
		{	
			iter->get()->TickInternal(deltaTime);
			++iter;
		}

		if (mCurrentStage != mGameStages.end())
			mCurrentStage->get()->TickStage(deltaTime);

		Tick(deltaTime);

		if (mHUD)
		{
			if(!mHUD->HasInit())
				mHUD->NativeInit(mOwningApp->GetWindow());

			mHUD->Tick(deltaTime);
		}
	}

	void World::Tick(float deltaTime)
	{
	}

	void World::RenderHUD(sf::RenderWindow& window)
	{
		if (mHUD)
			mHUD->Draw(window);
	}

	void World::InitGameStages()
	{

	}

	void World::AllGameStagesFinished()
	{
		LOG("ALL STAGES ARE FINISHED");
	}

	void World::NextGameStage()
	{
		mCurrentStage = mGameStages.erase(mCurrentStage);
		if (mCurrentStage != mGameStages.end())
		{
			mCurrentStage->get()->StartStage();
			mCurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
		}
		else
			AllGameStagesFinished();
	}

	void World::StartStages()
	{
		mCurrentStage = mGameStages.begin();

		if (mCurrentStage != mGameStages.end())
		{
			mCurrentStage->get()->StartStage();
			mCurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
		}
	}

	void World::BeginPlayingInternal()
	{
		if (!mBeginPlay)
		{
			mBeginPlay = true;
			BeginPLay();
			InitGameStages();
			StartStages();
		}
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto& actor : mActors)
		{
			actor->Render(window);
		}

		RenderHUD(window);
	}

	sf::Vector2u World::GetWindowSize() const
	{
		return mOwningApp->GetWindowSize();
	}

	void World::BeginPLay()
	{
	}

	void World::CleanCycle()
	{
		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			if (iter->get()->IsPendingDestroyed())
				iter = mActors.erase(iter);
			else
				++iter;
		}
	}

	void World::AddStage(const shared<GameStage>& newStage)
	{
		mGameStages.push_back(newStage);
	}

	bool World::DispatchEvent(const sf::Event& event)
	{
		if (mHUD)
			return mHUD->HandleEvent(event);

		return false;
	}
}