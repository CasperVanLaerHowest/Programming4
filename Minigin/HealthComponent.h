#pragma once
#include "Component.h"
#include "Subject.h"

class HealthComponent :
	public dae::Component,
	public dae::Subject
{
public:
	HealthComponent(int health);
	virtual ~HealthComponent() = default;
	virtual void FixedUpdate() override;

	void TakeDamage();
	int GetHealth() const { return m_Health; }

private:
	int m_Health;
	int m_MaxHealth;

	bool m_DirtyFlag = true;
};

