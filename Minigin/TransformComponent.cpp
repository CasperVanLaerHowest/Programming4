#include "TransformComponent.h"


TransformComponent::TransformComponent()
	: m_Position{ 0,0,0 }
	, m_Scale{ 1,1,1 }
	, m_Rotation{ 0,0,0 }
{
}

#pragma region Position
void TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

const glm::vec3& TransformComponent::GetPosition()
{
	return m_Position;
}
#pragma endregion Position
#pragma region Scale
void TransformComponent::SetScale(float x, float y, float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}

const glm::vec3& TransformComponent::GetScale()
{
	return m_Scale;
}
#pragma endregion Scale
#pragma region Rotation
void TransformComponent::SetRotation(float x, float y, float z)
{
	m_Rotation.x = x;
	m_Rotation.y = y;
	m_Rotation.z = z;
}

const glm::vec3& TransformComponent::GetRotation()
{
	return m_Rotation;
}
#pragma endregion Rotation