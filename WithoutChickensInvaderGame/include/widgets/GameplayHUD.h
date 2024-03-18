#pragma once
#include "widgets\HUD.h"
#include "widgets\TextWidget.h"
#include "widgets\ValueGuage.h"
#include "widgets\ImageWidget.h"

namespace wci
{
	class Actor;
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;
		void PlayerHealthUpdated(float amt, float currentHealth, float maxHealt);
		void RefreshHealthBar();
		void ConnectPlayerStatus();
		void PlayerLifeCountUpdated(int amt);
		void PlayerScoreUpdated(int newScore);
		void PlayerSapceshipDestroyed(Actor* actor);

		TextWidget mFramerateText;
		ValueGauge mPlayerHealthBar;
		ImageWidget mPlayerLifeIcon;
		TextWidget mPlayerLifeCountText;
		ImageWidget mPlayerScoreIcon;
		TextWidget mPlayerScoreText;

		sf::Color mHealthyHealthBarColor;
		sf::Color mCriticalHealthBarColor;

		float mCriticalThreshold;
		float mWidgetSpaceing;
	};
}