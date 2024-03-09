#include "level\GameLevelOne.h"
#include "framework\World.h"
#include "framework\Actor.h"
#include "player\PlayerSpaceship.h"
#include "framework\AssetManager.h"
#include "enemy\Vanguard.h"
#include "framework\TimerManager.h"
#include "gameplay\GameStage.h"
#include "enemy\VanguardStage.h"
#include "enemy\TwinBladeStage.h"
#include "gameplay\WaitStage.h"
#include "enemy\HexagonStage.h"
#include "enemy\UFOStage.h"
#include "enemy\UFO.h"

namespace wci
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		:World{owningApp}
	{
		testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 400.f));

		//weak<Vanguard> testSpaceship = SpawnActor<Vanguard>();
		//testSpaceship.lock()->SetActorLocation(sf::Vector2f(100.f, 50.f));
	}

	void GameLevelOne::BeginPLay()
	{
		/*weak<UFO> newUFO = SpawnActor<UFO>(sf::Vector2f{0.f, 0.f});
		newUFO.lock()->SetActorLocation({GetWindowSize().x / 2.f, GetWindowSize().y / 2.f});*/
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<UFOStage>{new UFOStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddStage(shared<VanguardStage>{new VanguardStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddStage(shared<HexagonStage>{new HexagonStage{ this }});
	}

}