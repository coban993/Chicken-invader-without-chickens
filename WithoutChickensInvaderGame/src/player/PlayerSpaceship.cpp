#include "player\PlayerSpaceship.h"
#include <SFML\System.hpp>
#include "framework\MathUtility.h"
#include "weapon\BulletShooter.h"
#include "weapon\ThreeWayShooter.h"
#include "weapon\FrontalWiper.h"

namespace wci
{
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
		:Spaceship{ owningWorld, path },
		mMoveInput{},
		mSpeed{ 200.f },
		mShooter{ new BulletShooter{this, 0.2f, {50.f, 0.f}} },
		mInvulnerableTime{ 2.f },
		mInvulnerable{ true },
		mInvulnerableFlashInterval{ 0.5f },
		mInvulnerableFlashTimer{ 0.f },
		mInvulnerableFlashDir{ 1 }
	{
		SetTeamID(1);
	}

	void PlayerSpaceship::Tick(float delatTime)
	{
		Spaceship::Tick(delatTime);
		HandleInput();
		ConsumeInput(delatTime);
		UpdateInvulnerable(delatTime);
	}

	void PlayerSpaceship::Shoot()
	{
		if (mShooter)
			mShooter->Shoot();
	}

	void PlayerSpaceship::ApplyDamage(float amt)
	{
		if (!mInvulnerable)
			Spaceship::ApplyDamage(amt);
	}

	void PlayerSpaceship::BeginPlay()
	{
		Spaceship::BeginPlay();
		TimeManager::Get().SetTimer(GetWeakRef(), &PlayerSpaceship::StopInvulnerable, mInvulnerableTime);
	}

	void PlayerSpaceship::SetShooter(unique<Shooter>&& newShooter)
	{
		if (mShooter && typeid(*mShooter.get()) == typeid(*newShooter.get()))
		{
			mShooter->IncrementLevel();
			return;
		}

		mShooter = std::move(newShooter);
	}

	void PlayerSpaceship::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			mMoveInput.y = -1.f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			mMoveInput.y = 1.f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			mMoveInput.x = -1.f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			mMoveInput.x = 1.f;

		ClampInputOnEdge();
		NormalizeInput();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			Shoot();
	}

	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		SetVelocity(mMoveInput * mSpeed);
		mMoveInput.x = mMoveInput.y = 0.f;
	}

	void PlayerSpaceship::NormalizeInput()
	{
		Normalize(mMoveInput);
	}

	void PlayerSpaceship::ClampInputOnEdge()
	{
		sf::Vector2f actorLocation = GetActorLocation();
		if (actorLocation.x < 55 && mMoveInput.x == -1)
			mMoveInput.x = 0.f;

		if (actorLocation.x > GetWindowSize().x - 55 && mMoveInput.x == 1.f)
			mMoveInput.x = 0.f;

		if (actorLocation.y < 55 && mMoveInput.y == -1)
			mMoveInput.y = 0.f;

		if (actorLocation.y > GetWindowSize().y - 55 && mMoveInput.y == 1.f)
			mMoveInput.y = 0.f;
	}

	void PlayerSpaceship::StopInvulnerable()
	{
		GetSprite().setColor({255,255,255,255});
		mInvulnerable = false;
	}

	void PlayerSpaceship::UpdateInvulnerable(float deltaTime)
	{
		if (!mInvulnerable) return;

		mInvulnerableFlashTimer += deltaTime * mInvulnerableFlashDir;

		if (mInvulnerableFlashTimer < 0 || mInvulnerableFlashTimer > mInvulnerableFlashInterval)
			mInvulnerableFlashDir *= -1;

		GetSprite().setColor(LerpColor({255,255,255,64}, {255,255,255,128}, mInvulnerableFlashTimer/mInvulnerableFlashInterval));
	}
}