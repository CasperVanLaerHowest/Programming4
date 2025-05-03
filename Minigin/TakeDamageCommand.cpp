#include "TakeDamageCommand.h"
#include "InputManager.h"

TakeDamageCommand::TakeDamageCommand(std::string player)
	: m_Player(player)
{
}
void TakeDamageCommand::Execute(bool notfirstExecute)
{
	if (!notfirstExecute)
	{

	}
}
