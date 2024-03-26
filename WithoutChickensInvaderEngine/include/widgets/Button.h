#pragma once
#include "widgets\Widget.h"
#include "framework\Delegate.h"

namespace wci
{
	class Button : public Widget
	{
	public:
		Button(const std::string& textString = "Button",
			const std::string& buttonTexturePath = "SpaceShooterRedux/PNG/UI/buttonGreen.png");

		virtual sf::FloatRect GetBound() const;
		void SetTextString(const std::string& newStr);
		void SetTextSize(unsigned int size);
		virtual bool HandleEvent(const sf::Event& windowEvent) override;

		Delegate<> onButtonClicked;

	private:
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void LocationUpdated(const sf::Vector2f& location) override;
		virtual void RotationUpdated(float rotation) override;
		void CenterText();
		void ButtonUp();
		void ButtonDown();
		void MouseHovered();

		shared<sf::Texture> mButtonTexture;
		sf::Sprite mButtonSprite;

		shared<sf::Font> mButtonFont;
		sf::Text mButtonText;

		sf::Color mButtonDefaultColor;
		sf::Color mButtonDownColor;
		sf::Color mButtonHoverColor;

		bool mIsButtonDown;
	};
}