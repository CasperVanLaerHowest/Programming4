#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"

dae::GameObject::~GameObject() = default;

dae::GameObject::GameObject()
{
	this->AddComponent<TransformComponent>();
}

void dae::GameObject::Update()
{
    for (const auto& component : m_pComponents)
    {
        component->Update();
    }
}

void dae::GameObject::Render() const
{
    for (const auto& component : m_pComponents)
    {
        component->Render();
    }
}

void dae::GameObject::FixedUpdate()
{
    for (const auto& component : m_pComponents)
    {
        component->FixedUpdate();
    }
}

void dae::GameObject::LateUpdate()
{
	for (const auto& component : m_pComponents)
	{
		component->LateUpdate();
	}

	// Update children
    auto transform = this->GetComponent<TransformComponent>();
	if (transform->GetDirtyFlag()) 
	{
		auto correctPos = transform->GetPosition() + transform->GetRotation();
		for (auto child : m_pChildren)
		{
			child->GetComponent<TransformComponent>()->SetRelativePosition(correctPos.x, correctPos.y, correctPos.z);
		}
		transform->SetDirtyFlag(false);
		
	}
}

void dae::GameObject::AddChild(GameObject* child)
{
	child->SetParent(this);
	m_pChildren.push_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	child->SetParent(nullptr);
	m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), child), m_pChildren.end());
}

void dae::GameObject::SetParent(GameObject* parent)
{
    m_pParent = parent;
}
