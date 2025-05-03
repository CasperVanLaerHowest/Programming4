#pragma once
#include "Component.h"

class HealthComponent :
    public dae::Component
{
public:
	HealthComponent(int health);
	virtual ~HealthComponent() = default;
	virtual void FixedUpdate() override;

	void TakeDamage();

private:
	int m_Health;
	int m_MaxHealth;

	bool m_DirtyFlag = true;
};

