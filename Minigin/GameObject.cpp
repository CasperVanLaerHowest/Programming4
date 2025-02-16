#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;


void dae::GameObject::Update()
{
    for (const auto& component : m_components)
    {
        component->Update();
    }
}

void dae::GameObject::Render() const
{
    for (const auto& component : m_components)
    {
        component->Render();
    }
}

void dae::GameObject::FixedUpdate()
{
    for (const auto& component : m_components)
    {
        component->FixedUpdate();
    }
}

//void dae::GameObject::Update()
//{
//	for (Component* pComponent : m_pComponents)
//	{
//		pComponent->Update();
//	}
//}

//void dae::GameObject::Render() const
//{
//	const auto& pos = m_transform.GetPosition();
//	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
//}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
//}

//void dae::GameObject::SetPosition(float x, float y)
//{
//	m_transform.SetPosition(x, y, 0.0f);
//}

//void dae::GameObject::AddComponent(Component* pComponent)
//{
//	// Add the component to the list of components
//	m_pComponents.push_back(pComponent);
//}


//void dae::GameObject::RemoveComponent(const std::string& name)
//{
//	// Find the component with the given name using a lambda function
//	auto comp = std::find_if(m_pComponents.begin(), m_pComponents.end(), [&name](Component* pComponent)
//		{
//			return typeid(pComponent).name() == name;
//		});
//	// If the component was found, remove it
//	if (comp != m_pComponents.end())
//	{
//		delete* comp;
//		m_pComponents.erase(comp);
//	}
//}

//Component* dae::GameObject::GetComponent(const std::string& name)
//{
//	// Find the component with the given name using a lambda function
//	auto comp = std::find_if(m_pComponents.begin(), m_pComponents.end(), [&name](Component* pComponent)
//		{
//			return static_cast<name>(pComponent);
//			return typeid(pComponent).name() == name;
//		});
//	// If the component was found, return it
//	if (comp != m_pComponents.end())
//	{
//		return*comp;
//	}
//	// If the component was not found, return a nullptr
//	return nullptr;
//}

//bool dae::GameObject::HasComponent(const std::string& name) const
//{
//	// Find the component with the given name using a lambda function
//	auto comp = std::find_if(m_pComponents.begin(), m_pComponents.end(), [&name](Component* pComponent)
//		{
//			return typeid(pComponent).name() == name;
//		});
//	// If the component was found, return true
//	if (comp != m_pComponents.end())
//	{
//		return true;
//	}
//	// If the component was not found, return false
//	return false;
//}