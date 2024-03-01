#pragma once
#include <memory>
#include <framework\Core.h>

namespace wci
{
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object();
		virtual	~Object();

		virtual void Destroy();
		bool IsPendingDestroyed() const { return mIsPendingDestroyed; }

		weak<Object> GetWeakRef();
		weak<const Object> GetWeakRef() const;

	private:
		bool mIsPendingDestroyed;
	};
}