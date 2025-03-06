#include "RotatorComponent.h"
#include "TransformComponent.h"
#include "GameObject.h" // Include the header file for GameObject
#include <math.h>
#include "Time.h"
#include <iostream>

RotatorComponent::RotatorComponent(float speed, float distance)
	: m_Speed{ speed },
	m_Distance{ distance }
{
}

void RotatorComponent::Update()
{
	auto transform = GetOwner()->GetComponent<TransformComponent>();
	glm::vec3 rotation = { 0,0,0 };
	rotation.x = (m_Distance * cos(m_CurrentAngle));
	rotation.y = (m_Distance * sin(m_CurrentAngle));

	transform->SetRotation(rotation.x, rotation.y, rotation.z);

	m_CurrentAngle += (m_Speed * Time::GetInstance().GetDeltaTime());

	//std::cout << "Current Angle: " << m_CurrentAngle << "  " << rotation.x << "  " << rotation.y << std::endl;

	//transform->SetRotation(transform->GetRotation().x + m_Speed, transform->GetRotation().y + m_Speed, transform->GetRotation().z + m_Speed);
}