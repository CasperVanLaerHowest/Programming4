#include "TakeDamageCommand.h"
#include "EventManager.h"
#include "InputManager.h"

TakeDamageCommand::TakeDamageCommand(std::string player)
	: m_Player(player)
{
}
void TakeDamageCommand::Execute(bool notfirstExecute)
{
	if (!notfirstExecute)
	{
		auto& EventManager = EventManager::GetInstance();
		EventManager.AddEvent(std::string{ m_Player + " takes damage" });
	}
}
