#include "TakeDamageCommand.h"
#include "InputManager.h"
#include "HealthComponent.h"
#include <iostream>

TakeDamageCommand::TakeDamageCommand(std::shared_ptr<dae::GameObject> Object)
	: m_Object(Object)
{
}
void TakeDamageCommand::Execute(bool notfirstExecute)
{
	if (!notfirstExecute)
	{
		std::cout << "TakeDamageCommand" << std::endl;
		m_Object->GetComponent<HealthComponent>()->TakeDamage();
	}
}
