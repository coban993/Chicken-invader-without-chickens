#include "gameFramework\GameApplication.h"
#include "framework\World.h"
#include "framework\Actor.h"
#include "config.h"
#include "player\PlayerSpaceship.h"
#include "framework\AssetManager.h"

wci::Application* GetApplication()
{
	return new wci::GameApplication{};
}

namespace wci
{
	GameApplication::GameApplication()
		:Application{600, 980, "Without chickens invader", sf::Style::Titlebar | sf::Style::Close}
	{
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());

		weak<World> newWorld = LoadWorld<World>();
		//newWorld.lock()->SpawnActor<Actor>();
		testPlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
		testPlayerSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_green.png");
		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 400.f));
		//testPlayerSpaceship.lock()->SetActorRotation(90.f);
		//testPlayerSpaceship.lock()->SetVelocity(sf::Vector2f(0.f, -200.f));

		weak<Spaceship> testSpaceship = newWorld.lock()->SpawnActor<Spaceship>();
		testSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_green.png");
		testSpaceship.lock()->SetActorLocation(sf::Vector2f(100.f, 50.f));
		testSpaceship.lock()->SetTeamID(2);

		counter = 0;
	}

	void GameApplication::Tick(float deltaTime)
	{
		/*counter += deltaTime;
		if (counter > 10.f)
		{
			if (!testPlayerSpaceship.expired())
				testPlayerSpaceship.lock()->Destroy();
		}*/
	}
}