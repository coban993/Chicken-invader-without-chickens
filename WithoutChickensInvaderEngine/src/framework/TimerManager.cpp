#include "framework\TimerManager.h"

namespace wci
{
	unsigned int TimerHandle::timerKeyCounter = 0;

	TimerHandle::TimerHandle()
		:mTimerKey{GetNexttimerKey()}
	{
	}

	bool operator==(const TimerHandle& lhs, const TimerHandle& rhs)
	{
		return lhs.GetTimerKey() == rhs.GetTimerKey();
	}

	Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat)
		:mListener{ weakRef, callback },
		mDuration{ duration },
		mRepeat{ repeat },
		mTimeCounter{ 0.f },
		mIsExpired{ false }
	{
	}

	void Timer::TickTime(float deltaTIme)
	{
		if (Expired()) return;

		mTimeCounter += deltaTIme;
		if (mTimeCounter >= mDuration)
		{
			mListener.second();
			if (mRepeat)
				mTimeCounter = 0.f;
			else
				SetExpired();
		}
	}

	bool Timer::Expired() const
	{
		return mIsExpired || mListener.first.expired() || mListener.first.lock()->IsPendingDestroyed();
	}

	void Timer::SetExpired()
	{
		mIsExpired = true;
	}

	unique<TimeManager> TimeManager::timerManager{ nullptr };

	TimeManager::TimeManager()
		:mTimers{}
	{
	}

	TimeManager& TimeManager::Get()
	{
		if (!timerManager)
			timerManager = std::move(unique<TimeManager>(new TimeManager{}));

		return *timerManager;
	}

	void TimeManager::UpdateTimer(float deltaTIme)
	{
		for (auto iter = mTimers.begin(); iter != mTimers.end();)
		{
			if (iter->second.Expired())
				iter = mTimers.erase(iter);
			else
			{
				iter->second.TickTime(deltaTIme);
				++iter;
			}
		}
	}

	void TimeManager::ClearTimer(TimerHandle timerHandle)
	{
		auto iter = mTimers.find(timerHandle);
		if (iter != mTimers.end())
			iter->second.SetExpired();
	}
}