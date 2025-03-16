#include "EventManager.h"
#include <iostream>

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::AddEvent(std::string event)
{
	m_Events.push_back(event);
}

void EventManager::RemoveEvent(std::string event)
{
	auto it = std::find(m_Events.begin(), m_Events.end(), event);
	if (it != m_Events.end())
	{
		m_Events.erase(it);
	}
}

bool EventManager::IsEventActive(std::string event)
{
	auto it = std::find(m_Events.begin(), m_Events.end(), event);
	if (it != m_Events.end())
	{
		return true;
	}
	return false;
}