#pragma once
#include <SFML\Graphics.hpp>
#include "framework\Object.h"

namespace wci
{
	class HUD : public Object
	{
	public:
		virtual void Draw(sf::RenderWindow& windowRef) = 0;
		virtual bool HandleEvent(const sf::Event& event);
		virtual void Tick(float deltaTime);

		void NativeInit(const sf::RenderWindow& windowRef);

		bool HasInit() { return mAlreadyInit; }

	protected:
		HUD();

	private:
		virtual void Init(const sf::RenderWindow& windowRef);
		bool mAlreadyInit;
	};
}