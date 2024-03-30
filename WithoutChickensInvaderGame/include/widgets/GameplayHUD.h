#pragma once
#include "widgets\HUD.h"
#include "widgets\TextWidget.h"
#include "widgets\ValueGuage.h"
#include "widgets\ImageWidget.h"
#include "widgets\Button.h"

namespace wci
{
	class Actor;
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float deltaTime) override;
		virtual bool HandleEvent(const sf::Event& event) override;
		void GameFinished(bool playerWon);

		Delegate<> onRestartButtonClicked;
		Delegate<> onQuitButtonClicked;

	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;
		void PlayerHealthUpdated(float amt, float currentHealth, float maxHealt);
		void RefreshHealthBar();
		void ConnectPlayerStatus();
		void PlayerLifeCountUpdated(int amt);
		void PlayerScoreUpdated(int newScore);
		void PlayerSapceshipDestroyed(Actor* actor);
		void RestartButtonClicked();
		void QuitButtonClicked();

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

		TextWidget mWinLoseText;
		TextWidget mFinalScoreText;
		Button mRestartButton;
		Button mQuitButton;

		sf::Vector2u mWindowSize;
	};
}