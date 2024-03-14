#pragma once
#include "widgets\HUD.h"
#include "widgets\TextWidget.h"
#include "widgets\ValueGuage.h"

namespace wci
{
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;

		TextWidget mFramerateText;
		ValueGauge mPlayerHealthBar;
	};
}