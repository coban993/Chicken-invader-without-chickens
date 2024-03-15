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
		mHealthyHealthBarColor{128,255,128,255},
		mCriticalHealthBarColor{255,0,0,255},
		mCriticalThreshold{0.3},
		mPlayerLifeIcon{ "SpaceShooterRedux/PNG/UI/playerLife2_green.png" },
		mWidgetSpaceing{10.f}
	{
		mFramerateText.SetTextSize(30);
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mFramerateText.NativeDraw(windowRef);
		mPlayerHealthBar.NativeDraw(windowRef);
		mPlayerLifeIcon.NativeDraw(windowRef);
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

		sf::Vector2f lifeIconPosition = mPlayerHealthBar.GetWidgetLocation();
		lifeIconPosition += sf::Vector2f{mPlayerHealthBar.GetBound().width + mWidgetSpaceing, 0.f};
		mPlayerLifeIcon.SetWidgetLocation(lifeIconPosition);

		RefreshHealthBar();
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

			mPlayerHealthBar.UpdateValue(healthComp.GetHealth(), healthComp.GetMaxHealth());
		}
	}

	void GameplayHUD::PlayerSapceshipDestroyed(Actor* actor)
	{
		RefreshHealthBar();
	}
}