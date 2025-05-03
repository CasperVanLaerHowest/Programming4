#pragma once
#include "GameObject.h"

namespace dae
{
	enum class Event
	{
		TAKE_DAMAGE,
		ADD_SCORE,
		PLAYER_DEAD,
		PLAYER_WON,
	};

	class Observer
	{
	private:
		virtual ~Observer() {}
	public:
		virtual void onNotify(const GameObject& entity, Event event) = 0;
	};
}
