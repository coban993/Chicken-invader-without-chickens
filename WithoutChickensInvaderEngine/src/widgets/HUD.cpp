#include "widgets\HUD.h"

namespace wci
{
	HUD::HUD()
		:mAlreadyInit{ false }
	{
	}

	bool HUD::HandleEvent(const sf::Event& event)
	{
		return false;
	}

	void HUD::Tick(float deltaTime)
	{
	}

	void HUD::NativeInit(const sf::RenderWindow& windowRef)
	{
		if (!mAlreadyInit)
		{
			mAlreadyInit = true;
			Init(windowRef);
		}
	}

	void HUD::Init(const sf::RenderWindow& windowRef)
	{
	}
}