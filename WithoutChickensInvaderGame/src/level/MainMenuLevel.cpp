#include "level\MainMenuLevel.h"
#include "widgets\MainMenuHUD.h"
#include "framework\Application.h"
#include "level\GameLevelOne.h"

namespace wci
{
	MainMenuLevel::MainMenuLevel(Application* owningApp)
		:World{owningApp}
	{
		mMainMenuHUD = SpawnHUD<MainMenuHUD>();
	}

	void MainMenuLevel::BeginPLay()
	{
		mMainMenuHUD.lock()->onStartButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::StartGame);
		mMainMenuHUD.lock()->onQuitButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::QuitGame);
	}

	void MainMenuLevel::StartGame()
	{
		GetApplication()->LoadWorld<GameLevelOne>();
	}

	void MainMenuLevel::QuitGame()
	{
		GetApplication()->QuitApplication();
	}
}