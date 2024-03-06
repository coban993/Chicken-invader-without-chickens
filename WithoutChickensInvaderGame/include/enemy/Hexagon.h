#pragma omce
#include "enemy\EnemySpaceship.h"

namespace wci
{
	class BulletShooter;
	class Hexagon : public EnemySpaceship
	{
	public:
		Hexagon(World* owningWorld, const std::string& textturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack4.png", const sf::Vector2f& velocity = sf::Vector2f{0.f, 100.f});

		virtual void Tick(float deltaTime) override;

	private:
		virtual void Shoot() override;

		unique<BulletShooter> mShooter1;
		unique<BulletShooter> mShooter2;
		unique<BulletShooter> mShooter3;
		unique<BulletShooter> mShooter4;
		unique<BulletShooter> mShooter5;
		unique<BulletShooter> mShooter6;
	};
}