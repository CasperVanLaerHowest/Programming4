#include "JumpCommand.h"
#include "GameObject.h"
#include <iostream>

JumpCommand::JumpCommand(std::shared_ptr<dae::GameObject> GameObject)
	: m_pGameObject{ GameObject }
{
}

void JumpCommand::Execute()
{
	std::cout << "JumpCommand executed" << std::endl;
}