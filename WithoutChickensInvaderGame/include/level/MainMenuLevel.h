#pragma once
#include "framework\World.h"

namespace wci
{
	class MainMenuHUD;
	class MainMenuLevel : public World
	{
	public:
		MainMenuLevel(Application* owningApp);

		virtual void BeginPLay() override;

	private:
		void StartGame();
		void QuitGame();

		weak<MainMenuHUD> mMainMenuHUD;
	};
}