#pragma once
#include "Command.h"
#include "GameObject.h"

class JumpCommand :
    public Command
{
public:
	JumpCommand(std::shared_ptr<dae::GameObject> GameObject);
	virtual void Execute(bool notfirstExecute) override;

private:
	std::shared_ptr<dae::GameObject> m_pGameObject;
};

