#include "framework\Object.h"
#include "framework\Core.h"

namespace wci
{
	unsigned int Object::uniqueIDCounter = 0;
	Object::Object()
		:mIsPendingDestroyed{false},
		mUniqueID{GetNextAvaliableID()}
	{
	}

	Object::~Object()
	{
		LOG("object is destroyed");
	}

	void Object::Destroy()
	{
		onDestroy.Broadcast(this);
		mIsPendingDestroyed = true;
	}

	weak<Object> Object::GetWeakRef()
	{
		return weak_from_this();
	}

	weak<const Object> Object::GetWeakRef() const
	{
		return weak_from_this();
	}

	unsigned int Object::GetNextAvaliableID()
	{
		return uniqueIDCounter++;
	}
}


