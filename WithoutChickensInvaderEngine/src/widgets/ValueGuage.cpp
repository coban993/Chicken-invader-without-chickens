#include "widgets\ValueGuage.h"
#include "framework\AssetManager.h"

namespace wci
{
	ValueGauge::ValueGauge(const sf::Vector2f& size, float initialPercent, const sf::Color& foregroundColor, const sf::Color& backgroundColor)
		:mFont{ AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf") },
		mText{ "sdadad", *(mFont.get()) },
		mBarFront{ size },
		mBarBack{ size },
		mPercent{ initialPercent },
		mForegroundColor{foregroundColor},
		mBackgroundColor{backgroundColor}
	{
		mBarFront.setFillColor(mForegroundColor);
		mBarBack.setFillColor(mBackgroundColor);
	}

	void ValueGauge::UpdateValue(float value, float maxValue)
	{
		if (maxValue == 0) return;

		mPercent = value / maxValue;
		std::string displayStr = std::to_string((int)value) + "/" + std::to_string((int)maxValue);
		mText.setString(displayStr);

		sf::Vector2f barSize = mBarBack.getSize();
		mBarFront.setSize({ barSize.x * mPercent, barSize.y });
	}

	void ValueGauge::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mBarBack);
		windowRef.draw(mBarFront);
		windowRef.draw(mText);
	}

	void ValueGauge::LocationUpdated(const sf::Vector2f& newLoc)
	{
		mText.setPosition(newLoc);
		mBarFront.setPosition(newLoc);
		mBarBack.setPosition(newLoc);
	}

	void ValueGauge::RotationUpdated(float newRotation)
	{
		mText.setRotation(newRotation);
		mBarFront.setRotation(newRotation);
		mBarBack.setRotation(newRotation);
	}
}