#include "MoveCommand.h"
#include "TransformComponent.h"
#include "GameTime.h"

MoveCommand::MoveCommand(std::shared_ptr<dae::GameObject> GameObject, Direction direction)
	: m_pGameObject{ GameObject }, m_Direction{ direction }
{
	m_Speed = 100.0f;
	//m_Transform = m_pGameObject->GetComponent<TransformComponent>();
}

void MoveCommand::Execute(bool notfirstExecute)
{
	if (notfirstExecute)
	{
		//std::cout << "first MoveCommand executed" << std::endl;
	}
	
	auto transform = m_pGameObject->GetComponent<TransformComponent>();
	auto pos = transform->GetPosition();
	

	switch (m_Direction)
	{
	case Direction::UP:
		if (CollisionManager.CheckCollision(m_pGameObject,dae::TypeObject::LADDER)) {
			transform->SetPosition(pos.x, pos.y - (m_Speed * GameTime::GetInstance().GetDeltaTime()), pos.z);
		}
		break;
	case Direction::DOWN:
		if (CollisionManager.CheckBottomCollision(m_pGameObject,dae::TypeObject::LADDER)) {
			transform->SetPosition(pos.x, pos.y + (m_Speed * GameTime::GetInstance().GetDeltaTime()), pos.z);
		}
		
		break;
	case Direction::LEFT:
		if (CollisionManager.CheckBottomCollision(m_pGameObject, dae::TypeObject::PLATFORM))
		{
			float y = CollisionManager.GetYCollision(m_pGameObject, dae::TypeObject::PLATFORM);
			transform->SetPosition(pos.x - (m_Speed * GameTime::GetInstance().GetDeltaTime()), y, pos.z);
		}
		break;
	case Direction::RIGHT:
		if (CollisionManager.CheckBottomCollision(m_pGameObject, dae::TypeObject::PLATFORM))
		{
			float y = CollisionManager.GetYCollision(m_pGameObject, dae::TypeObject::PLATFORM);
			transform->SetPosition(pos.x + (m_Speed * GameTime::GetInstance().GetDeltaTime()), y, pos.z);
		}
		break;
	case Direction::NONE:
		//m_pGameObject->GetComponent<MovementComponent>()->SetDirection(std::pair(0, 0));
		break;
	}
}