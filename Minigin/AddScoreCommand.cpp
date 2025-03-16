#include "AddScoreCommand.h"
#include "EventManager.h"
#include "InputManager.h"

AddScoreCommand::AddScoreCommand(std::string player)
	: m_Player(player)
{
}

void AddScoreCommand::Execute(bool notfirstExecute)
{
	if (!notfirstExecute)
	{
		auto& EventManager = EventManager::GetInstance();
		EventManager.AddEvent(std::string{ m_Player + " add score" });
	}
}
