#pragma once
#include "Component.h"
#include "EventManager.h"
class HealthComponent :
    public dae::Component
{
public:
	HealthComponent(int health, std::string player);
	virtual ~HealthComponent() = default;
	virtual void FixedUpdate() override;

	void ProcessEvents();
	void ListenEvent(EventManager&);
	void WriteEvent(EventManager&);

private:
	int m_Health;
	int m_MaxHealth;

	bool m_DirtyFlag = true;
	std::string m_Event;

	void TakeDamage();
};

