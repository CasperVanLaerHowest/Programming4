#pragma once
#include "Singleton.h"
#include <vector>
#include <string>

class EventManager final : public dae::Singleton<EventManager>
{
public:
	EventManager();
	~EventManager();
	void AddEvent(std::string event);
	void RemoveEvent(std::string event);
	bool IsEventActive(std::string event);
private:
	std::vector<std::string> m_Events;
};

