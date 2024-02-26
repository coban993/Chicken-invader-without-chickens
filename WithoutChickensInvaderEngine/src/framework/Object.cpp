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
}


