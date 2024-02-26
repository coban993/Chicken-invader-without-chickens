#pragma once
#include <framework\Application.h>
#include "framework\Core.h"

namespace wci
{
	class PlayerSpaceship;
	class Actor;
	class GameApplication : public Application
	{
	public:
		GameApplication();

		virtual void Tick(float deltaTime) override;

	private:
		float counter;
		weak<PlayerSpaceship> testPlayerSpaceship;
	};
}