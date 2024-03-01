#include "VFX\Explosion.h"
#include "framework\MathUtility.h"
#include "VFX\Particle.h"
#include "framework\World.h"

namespace wci
{
	Explosion::Explosion(int particleAmount, float lifeTimeMin, float lifeTimeMax, float sizeMin, float sizeMax, float speedMin, float speedMax, const sf::Color& particleColor, const List<std::string>& particleImagePaths)
		: mParticleAmount{particleAmount},
		mLifetimeMin{lifeTimeMin},
		mLifetimeMax{lifeTimeMax},
		mSizeMin{sizeMin},
		mSizeMax{sizeMax},
		mSpeedMin{speedMin},
		mSpeedMax{speedMax},
		mParticleColor{particleColor},
		mParticleImagePaths{particleImagePaths}
	{
	}

	void Explosion::SpawnExplosion(World* world, const sf::Vector2f& location)
	{
		if (!world) return;

		for (int i = 0; i < mParticleAmount; ++i)
		{
			std::string particleImagePath = mParticleImagePaths[(int)RandomRange(0, mParticleImagePaths.size())];
			weak<Particle> newParticle = world->SpawnActor<Particle>(particleImagePath);

			newParticle.lock()->RandomLifeTime(mLifetimeMin, mLifetimeMax);
			newParticle.lock()->SetActorLocation(location);
			newParticle.lock()->RandomSize(mSizeMin, mSizeMax);
			newParticle.lock()->RandomVelocity(mSpeedMin, mSpeedMax);
			newParticle.lock()->GetSprite().setColor(mParticleColor);
		}
	}
}