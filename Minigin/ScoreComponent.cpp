#include "ScoreComponent.h"
#include "TextRenderer.h"
#include "GameObject.h" // Add this include to resolve the incomplete type error
#include <iostream>

ScoreComponent::ScoreComponent(std::string player)
	: m_Event{ player }
{
}

void ScoreComponent::FixedUpdate()
{
	ProcessEvents();
	if (m_DirtyFlag)
	{
		this->GetOwner()->GetComponent<TextRenderer>()->SetText("Score: " + std::to_string(m_Score));
		m_DirtyFlag = false;
	}
}

void ScoreComponent::ProcessEvents()
{
	auto& eventManager = EventManager::GetInstance();
	ListenEvent(eventManager);
	//WriteEvent(eventManager);
}

void ScoreComponent::ListenEvent(EventManager& eventManager)
{
	if (eventManager.IsEventActive(std::string{ m_Event + " add score" }))
	{
		AddScore();
		eventManager.RemoveEvent(std::string{ m_Event + " add score" });
	}
}

//void ScoreComponent::WriteEvent(EventManager& eventManager)
//{
//	if (m_Score >= 500)
//	{
//		//eventManager.AddEvent(std::string{ m_Event + " won" });
//		std::cout << m_Event << " won" << std::endl;
//	}
//}

void ScoreComponent::AddScore()
{
	m_Score += 100;
	m_DirtyFlag = true;
}
