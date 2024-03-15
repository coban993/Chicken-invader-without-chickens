#pragma once
#include <SFML\Graphics.hpp>
#include "framework\Object.h"

namespace wci
{
	class Widget : public Object
	{
	public:
		void NativeDraw(sf::RenderWindow& windowRef);
		virtual bool HandleEvent(const sf::Event& event);

		sf::Vector2f GetWidgetLocation() const { return mWidgetTransform.getPosition(); }
		void SetWidgetLocation(const sf::Vector2f& newLocation);

		float GetWidgetRotation() const { return mWidgetTransform.getRotation(); }
		void SetWidgetRotation(float newRotation);

		bool GetVisibility() const { return mIsVisible; }
		void SetVisibility(bool newVisibility);

		virtual sf::FloatRect GetBound() const;
		sf::Vector2f GetCenterPosition() const;

	protected:
		Widget();

	private:
		virtual void Draw(sf::RenderWindow& windowRef);
		virtual void LocationUpdated(const sf::Vector2f& newLocation);
		virtual void RotationUpdated(float newRotation);

		sf::Transformable mWidgetTransform;
		bool mIsVisible;
	};
}