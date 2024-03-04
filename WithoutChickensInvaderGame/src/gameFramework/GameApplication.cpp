#include "gameFramework\GameApplication.h"
#include "level\GameLevelOne.h"
#include "config.h"
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

		weak<GameLevelOne> newWorld = LoadWorld<GameLevelOne>();
		newWorld.lock()->BeginPlayingInternal();
	}
}