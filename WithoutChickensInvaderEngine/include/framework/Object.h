#pragma once

namespace wci
{
	class Object
	{
	public:
		Object();
		virtual	~Object();

		virtual void Destroy();
		bool IsPendingDestroyed() const { return mIsPendingDestroyed; }

	private:
		bool mIsPendingDestroyed;
	};
}