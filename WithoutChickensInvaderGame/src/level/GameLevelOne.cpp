#include "level\GameLevelOne.h"
#include "framework\World.h"
#include "framework\Actor.h"
#include "player\PlayerSpaceship.h"
#include "framework\AssetManager.h"
#include "enemy\Vanguard.h"
#include "framework\TimerManager.h"

namespace wci
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		:World{owningApp}
	{
		testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 400.f));

		weak<Vanguard> testSpaceship = SpawnActor<Vanguard>();
		testSpaceship.lock()->SetActorLocation(sf::Vector2f(100.f, 50.f));
	}

	void GameLevelOne::BeginPLay()
	{
		timerHandle_test = TimeManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallback_Test, 2, true);
	}

	void GameLevelOne::TimerCallback_Test()
	{
		LOG("callback called");
		TimeManager::Get().ClearTimer(timerHandle_test);
	}
}