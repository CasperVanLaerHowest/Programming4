#pragma once
#include "Component.h"
#include <glm.hpp>
class TransformComponent final:
    public dae::Component
{
public:

	TransformComponent();
	virtual ~TransformComponent() = default;

	virtual void Update() override;

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

	void SetRelativePosition(float x, float y, float z);
	const glm::vec3& GetRelativePosition();

	bool GetDirtyFlag() const { return m_IsDirty; }
	void SetDirtyFlag(bool flag) { m_IsDirty = flag; }

private:

	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_Rotation;

	//if you are a child of a parent object, you can use this to update a position relative to the parent
	glm::vec3 m_RelativePosition;

	bool m_IsDirty = false;
};

