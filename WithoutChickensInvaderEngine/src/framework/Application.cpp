#include "framework\Application.h"
#include "framework\Core.h"
#include "framework\World.h"
#include "framework\AssetManager.h"
#include "framework\Physics.h"
#include "framework\TimerManager.h"

namespace wci
{
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
		:mWindow{ sf::VideoMode(windowWidth,  windowHeight), title, style },
		mTargetFrameRate(60.f),
		mTickClock{},
		mCurrentWorld{ nullptr },
		mCleanCycleClock{},
		mCleanCycleInterval{ 2.f }
	{
	}

	void Application::Run()
	{
		mTickClock.restart();
		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / mTargetFrameRate;

		while (mWindow.isOpen())
		{
			sf::Event windowEvent;
			while (mWindow.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
					mWindow.close();
				else
					Dispatch(windowEvent);
			}

			float frameDeltaTime = mTickClock.restart().asSeconds();
			accumulatedTime += frameDeltaTime;
			while (accumulatedTime > targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;
				TickInternal(targetDeltaTime);
				RenderInternal();
			}
		}
	}

	void Application::RenderInternal()
	{
		mWindow.clear();

		Render();

		mWindow.display();
	}

	void Application::Render()
	{
		if (mCurrentWorld)
		{
			mCurrentWorld->Render(mWindow);
		}
	}

	sf::Vector2u Application::GetWindowSize() const
	{
		return mWindow.getSize();
	}

	bool Application::Dispatch(const sf::Event& event)
	{
		if (mCurrentWorld)
			return mCurrentWorld->DispatchEvent(event);

		return false;
	}

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);

		if (mCurrentWorld)
			mCurrentWorld->TickInternal(deltaTime);

		TimeManager::Get().UpdateTimer(deltaTime);
		Physics::Get().Step(deltaTime);

		if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval)
		{
			mCleanCycleClock.restart();
			AssetManager::Get().CleanCycle();
			if (mCurrentWorld)
				mCurrentWorld->CleanCycle();
		}
	}

	void Application::Tick(float deltaTime)
	{

	}
}
