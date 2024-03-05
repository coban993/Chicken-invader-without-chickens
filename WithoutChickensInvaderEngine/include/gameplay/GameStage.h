#pragma once
#include "framework\Object.h"
#include "framework\Delegate.h"

namespace wci
{
	class World;
	class GameStage : public Object
	{
	public:
		GameStage(World* world);
		const World* GetWorld() const { return mWorld; }
		World* GetWorld() { return mWorld; }

		Delegate<> onStageFinished;

		virtual void StartStage();
		virtual void TickStage(float deltaTime);
		virtual void FinishStage();

		bool IsStageFinished() const { return mStageFinished; }

	private:
		virtual void StageFinished();

		World* mWorld;
		bool mStageFinished;
	};
}