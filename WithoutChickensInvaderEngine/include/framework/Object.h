#pragma once
#include <framework\Core.h>
#include <memory>
#include "framework\Delegate.h"

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
		Delegate<Object*> onDestroy;
		unsigned int GetUniqueID() const { return mUniqueID; }

	private:
		bool mIsPendingDestroyed;
		unsigned int mUniqueID;

		static unsigned int uniqueIDCounter;
		static unsigned int GetNextAvaliableID();
	};
}