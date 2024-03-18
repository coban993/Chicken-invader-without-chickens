#include "widgets\GameplayHUD.h"
#include "player\PlayerManager.h"
#include "player\PlayerSpaceship.h"
#include "player\Player.h"
#include "framework\Actor.h"

namespace wci
{
	GameplayHUD::GameplayHUD()
		:mFramerateText{"FPS:"},
		mPlayerHealthBar{},
		mPlayerLifeIcon{ "SpaceShooterRedux/PNG/UI/playerLife2_green.png" },
		mPlayerLifeCountText{ "" },
		mPlayerScoreIcon{ "SpaceShooterRedux/PNG/Power-ups/star_gold.png" },
		mPlayerScoreText{ "" },
		mHealthyHealthBarColor{128,255,128,255},
		mCriticalHealthBarColor{255,0,0,255},
		mCriticalThreshold{0.3},
		mWidgetSpaceing{10.f}
	{
		mFramerateText.SetTextSize(30);
		mPlayerLifeCountText.SetTextSize(20);
		mPlayerScoreText.SetTextSize(20);
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mFramerateText.NativeDraw(windowRef);
		mPlayerHealthBar.NativeDraw(windowRef);
		mPlayerLifeIcon.NativeDraw(windowRef);
		mPlayerLifeCountText.NativeDraw(windowRef);
		mPlayerScoreIcon.NativeDraw(windowRef);
		mPlayerScoreText.NativeDraw(windowRef);
	}

	void GameplayHUD::Tick(float deltaTime)
	{
		int frameRate = int(1 / deltaTime);
		std::string frameRateStr = "FPS: " + std::to_string(frameRate);
		mFramerateText.SetString(frameRateStr);
	}

	void GameplayHUD::Init(const sf::RenderWindow& windowRef)
	{
		auto windowSize = windowRef.getSize();
		mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{20.f, windowSize.y - 50.f});

		sf::Vector2f nextWidgetPosition = mPlayerHealthBar.GetWidgetLocation();

		nextWidgetPosition += sf::Vector2f{mPlayerHealthBar.GetBound().width + mWidgetSpaceing, 0.f};
		mPlayerLifeIcon.SetWidgetLocation(nextWidgetPosition);

		nextWidgetPosition += sf::Vector2f{ mPlayerLifeIcon.GetBound().width + mWidgetSpaceing, 0.f };
		mPlayerLifeCountText.SetWidgetLocation(nextWidgetPosition);

		nextWidgetPosition += sf::Vector2f{ mPlayerLifeCountText.GetBound().width + mWidgetSpaceing * 4, -2.f };
		mPlayerScoreIcon.SetWidgetLocation(nextWidgetPosition);

		nextWidgetPosition += sf::Vector2f{ mPlayerScoreIcon.GetBound().width + mWidgetSpaceing, 0.f };
		mPlayerScoreText.SetWidgetLocation(nextWidgetPosition);

		RefreshHealthBar();
		ConnectPlayerStatus();
	}

	void GameplayHUD::PlayerHealthUpdated(float amt, float currentHealth, float maxHealt)
	{
		mPlayerHealthBar.UpdateValue(currentHealth, maxHealt);

		if (currentHealth / maxHealt < mCriticalThreshold)
			mPlayerHealthBar.SetForegroundColor(mCriticalHealthBarColor);
		else
			mPlayerHealthBar.SetForegroundColor(mHealthyHealthBarColor);
	}

	void GameplayHUD::RefreshHealthBar()
	{
		Player* player = PlayerManager::Get().GetPlayer();

		if (player && !player->GetCurrentSpaceship().expired())
		{
			weak<PlayerSpaceship> playerSpaceship = player->GetCurrentSpaceship();
			playerSpaceship.lock()->onActorDestoryed.BindAction(GetWeakRef(), &GameplayHUD::PlayerSapceshipDestroyed);

			HealthComponent& healthComp = player->GetCurrentSpaceship().lock()->GetHealthComponent();
			healthComp.onHealthChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerHealthUpdated);

			PlayerHealthUpdated(0, healthComp.GetHealth(), healthComp.GetMaxHealth());
		}
	}

	void GameplayHUD::ConnectPlayerStatus()
	{
		Player* player = PlayerManager::Get().GetPlayer();

		if (player)
		{
			int lifeCount = player->GetLifeCount();
			mPlayerLifeCountText.SetString(std::to_string(lifeCount));
			player->onLifeChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerLifeCountUpdated);

			int playerScore = player->GetScore();
			mPlayerScoreText.SetString(std::to_string(playerScore));
			player->onScoreChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerScoreUpdated);
		}
	}

	void GameplayHUD::PlayerLifeCountUpdated(int amt)
	{
		mPlayerLifeCountText.SetString(std::to_string(amt));
	}

	void GameplayHUD::PlayerScoreUpdated(int newScore)
	{
		mPlayerScoreText.SetString(std::to_string(newScore));
	}

	void GameplayHUD::PlayerSapceshipDestroyed(Actor* actor)
	{
		RefreshHealthBar();
	}
}