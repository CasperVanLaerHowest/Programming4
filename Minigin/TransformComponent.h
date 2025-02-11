#pragma once
#include "Component.h"
#include <glm.hpp>
class TransformComponent final:
    public Component
{
public:

	TransformComponent() = default;
	virtual ~TransformComponent() = default;
	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;
	//void Update() override;

	void SetPosition(float x, float y, float z);
	const glm::vec3& GetPosition();

	void SetScale(float x, float y, float z);
	const glm::vec3& GetScale();

	void SetRotation(float x, float y, float z);
	const glm::vec3& GetRotation();

private:

	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_Rotation;

};

