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
#include "player\PlayerManager.h"
#include "widgets\GameplayHUD.h"
#include "enemy\ChaosStage.h"
#include "enemy\BossStage.h"

namespace wci
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		:World{owningApp}
	{
	}

	void GameLevelOne::BeginPLay()
	{
		Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
		mPlayerSpaceship = newPlayer.SpawnSpaceship(this);
		mPlayerSpaceship.lock()->onActorDestoryed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		mGameplayHUD = SpawnHUD<GameplayHUD>();
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<BossStage>{new BossStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddStage(shared<VanguardStage>{new VanguardStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 15.f }});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 12.f }});
		AddStage(shared<HexagonStage>{new HexagonStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 10.f }});
		AddStage(shared<UFOStage>{new UFOStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddStage(shared<ChaosStage>{new ChaosStage{ this }});
	}

	void GameLevelOne::PlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship)
	{
		mPlayerSpaceship = PlayerManager::Get().GetPlayer()->SpawnSpaceship(this);

		if (!mPlayerSpaceship.expired())
			mPlayerSpaceship.lock()->onActorDestoryed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		else
			GameOver();
	}

	void GameLevelOne::GameOver()
	{
		LOG("GAME OVER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	}
}