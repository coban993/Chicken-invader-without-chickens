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
		SetTextSize(20);
	}

	void ValueGauge::UpdateValue(float value, float maxValue)
	{
		if (maxValue == 0) return;

		mPercent = value / maxValue;
		std::string displayStr = std::to_string((int)value) + "/" + std::to_string((int)maxValue);
		mText.setString(displayStr);

		sf::Vector2f barSize = mBarBack.getSize();
		mBarFront.setSize({ barSize.x * mPercent, barSize.y });
		CenterText();
	}

	sf::FloatRect ValueGauge::GetBound() const
	{
		return mBarBack.getGlobalBounds();
	}

	void ValueGauge::SetTextSize(unsigned int characterSize)
	{
		mText.setCharacterSize(characterSize);
	}

	void ValueGauge::SetForegroundColor(const sf::Color& color)
	{
		mBarFront.setFillColor(color);
	}

	void ValueGauge::SetBackgroundColor(const sf::Color& color)
	{
		mBarBack.setFillColor(color);
	}

	void ValueGauge::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mBarBack);
		windowRef.draw(mBarFront);
		windowRef.draw(mText);
	}

	void ValueGauge::LocationUpdated(const sf::Vector2f& newLoc)
	{
		mBarFront.setPosition(newLoc);
		mBarBack.setPosition(newLoc);
		CenterText();
	}

	void ValueGauge::RotationUpdated(float newRotation)
	{
		mText.setRotation(newRotation);
		mBarFront.setRotation(newRotation);
		mBarBack.setRotation(newRotation);
	}

	void ValueGauge::CenterText()
	{
		sf::Vector2f widgetCenter = GetCenterPosition();
		sf::FloatRect textBound = mText.getGlobalBounds();
		mText.setPosition(widgetCenter - sf::Vector2f{textBound.width/2.f, textBound.height});
	}
}