#pragma once
#include "Command.h"
#include "GameObject.h"
#include <glm.hpp>

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

class MoveCommand :
    public Command
{
public:
	MoveCommand(std::shared_ptr<dae::GameObject> GameObject, Direction direction);
	virtual void Execute(bool notfirstExecute) override;
	//void SetDirection(glm::vec3& direction) { m_Direction = direction; }

private:
	std::shared_ptr<dae::GameObject> m_pGameObject;
	Direction m_Direction;

	float m_Speed;
};

