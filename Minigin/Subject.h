#pragma once
#include "Observer.h"
#include "GameObject.h"

namespace dae
{
	class Subject
	{
	public:
		void AddObserver(dae::Observer* observer)
		{
			if (numObservers_ < MAX_OBSERVERS)
			{
				observers_[numObservers_] = observer;
				numObservers_++;
			}
		}
		void RemoveObserver(dae::Observer* observer)
		{
			for (int i = 0; i < numObservers_; ++i)
			{
				if (observers_[i] == observer)
				{
					observers_[i] = observers_[numObservers_ - 1];
					numObservers_--;
					break;
				}
			}
		}
	protected:
		void Notify(dae::GameObject& entity, dae::Event event)
		{
			for (int i = 0; i < numObservers_; ++i)
			{
				observers_[i]->onNotify(entity, event);
			}
		}

	private:
		static const int MAX_OBSERVERS{ 10 };
		dae::Observer* observers_[MAX_OBSERVERS];
		int numObservers_{ 0 };
	};
}

// This class is a simple implementation of the Observer pattern.