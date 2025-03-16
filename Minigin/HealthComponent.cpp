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
	ProcessEvents();
	if (m_DirtyFlag)
	{
		this->GetOwner()->GetComponent<TextRenderer>()->SetText("Health: " + std::to_string(m_Health));
		m_DirtyFlag = false;
	}
}

void HealthComponent::ProcessEvents()
{
	auto& eventManager = EventManager::GetInstance();
	ListenEvent(eventManager);
	WriteEvent(eventManager);
}

void HealthComponent::ListenEvent(EventManager& eventManager)
{
	//auto& eventManager = EventManager::GetInstance();
	if (eventManager.IsEventActive(std::string{m_Event + " takes damage"}))
	{
		TakeDamage();
		eventManager.RemoveEvent(std::string{ m_Event + " takes damage" });
	}
}

void HealthComponent::WriteEvent(EventManager& eventManager)
{
	//auto& eventManager = EventManager::GetInstance();
	if (m_Health <= 0) 
	{
		eventManager.AddEvent(std::string{ m_Event + " died" });
	}
}

void HealthComponent::TakeDamage()
{
	m_Health -= 1;
	m_DirtyFlag = true;
}