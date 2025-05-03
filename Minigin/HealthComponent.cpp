#include "HealthComponent.h"
#include "TextRenderer.h"
#include "GameObject.h"

HealthComponent::HealthComponent(int health, std::string player)
	: m_Health{ health }
	, m_MaxHealth{ health },
	m_Event{ player }
{
	//this->GetOwner()->GetComponent<TextRenderer>()->SetText("Health: " + std::to_string(m_Health));
}

void HealthComponent::FixedUpdate()
{
	if (m_DirtyFlag)
	{
		this->GetOwner()->GetComponent<TextRenderer>()->SetText("Health: " + std::to_string(m_Health));
		m_DirtyFlag = false;
	}
}

void HealthComponent::TakeDamage()
{
	m_Health -= 1;
	m_DirtyFlag = true;
}