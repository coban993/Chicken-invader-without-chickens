#include "framework\Object.h"
#include "framework\Core.h"

namespace wci
{
	Object::Object()
		:mIsPendingDestroyed{false}
	{
	}

	Object::~Object()
	{
		LOG("object is destroyed");
	}

	void Object::Destroy()
	{
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
}


