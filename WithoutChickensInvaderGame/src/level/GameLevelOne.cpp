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
#include "framework\Application.h"
#include "framework\BackdropActor.h"
#include "framework\BackgroundLayer.h"

namespace wci
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		:World{owningApp}
	{
	}

	void GameLevelOne::BeginPLay()
	{
		SpawnCosmetics();

		Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
		mPlayerSpaceship = newPlayer.SpawnSpaceship(this);
		mPlayerSpaceship.lock()->onActorDestoryed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		mGameplayHUD = SpawnHUD<GameplayHUD>();
		mGameplayHUD.lock()->onQuitButtonClicked.BindAction(GetWeakRef(), &GameLevelOne::QuitGame);
		mGameplayHUD.lock()->onRestartButtonClicked.BindAction(GetWeakRef(), &GameLevelOne::Restart);
	}

	void GameLevelOne::InitGameStages()
	{
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

		AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddStage(shared<BossStage>{new BossStage{ this }});
	}

	void GameLevelOne::AllGameStagesFinished()
	{
		mGameplayHUD.lock()->GameFinished(true);
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
		mGameplayHUD.lock()->GameFinished(false);
	}

	void GameLevelOne::QuitGame()
	{
		GetApplication()->QuitApplication();
	}

	void GameLevelOne::Restart()
	{
		PlayerManager::Get().Reset();
		GetApplication()->LoadWorld<GameLevelOne>();
	}

	void GameLevelOne::SpawnCosmetics()
	{
		auto backdropActor = SpawnActor<BackdropActor>("SpaceShooterRedux/Backgrounds/darkPurple.png");
		weak<BackgroundLayer> planets = SpawnActor<BackgroundLayer>();
		planets.lock()->SetAssets(
			{
				"SpaceShooterRedux/PNG/planets/Planet1.png",
				"SpaceShooterRedux/PNG/planets/Planet2.png",
				"SpaceShooterRedux/PNG/planets/Planet3.png",
				"SpaceShooterRedux/PNG/planets/Planet4.png",
				"SpaceShooterRedux/PNG/planets/Planet5.png",
				"SpaceShooterRedux/PNG/planets/Planet6.png",
				"SpaceShooterRedux/PNG/planets/Planet7.png"
			}
		);

		planets.lock()->SetSpriteCount(1);
		planets.lock()->SetSizes(0.8f, 1.2f);
		planets.lock()->SetVelocities({0, 30.f}, {0, 80.f});

		weak<BackgroundLayer> meteors = SpawnActor<BackgroundLayer>();
		meteors.lock()->SetAssets(
			{
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big4.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_med1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_med3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_small1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_small2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big4.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_med1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_med2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_small1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_small2.png",
			}
		);

		meteors.lock()->SetSpriteCount(20);
		meteors.lock()->SetSizes(0.2f, 0.5f);
	}
}