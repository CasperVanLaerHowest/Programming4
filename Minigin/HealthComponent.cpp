#include "HealthComponent.h"
#include "TextRenderer.h"
#include "GameObject.h"

HealthComponent::HealthComponent(int health)
	: m_Health{ health }
	, m_MaxHealth{ health }
{
}

void HealthComponent::FixedUpdate()
{
	if (m_DirtyFlag)
	{
		if (m_Health <= 0)
		{
			this->GetOwner()->Notify(dae::Event::PLAYER_DEAD);
		}
		m_DirtyFlag = false;
	}
}

void HealthComponent::TakeDamage()
{
	this->GetOwner()->Notify(dae::Event::TAKE_DAMAGE);
	m_Health -= 1;
	m_DirtyFlag = true;
}