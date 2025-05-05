#pragma once
#include <memory>
#include <vector>
#include "Component.h"
//#include "Transform.h"

namespace dae
{
	//class Texture2D;

	class GameObject final
	{
	public:
		virtual void Update();
		virtual void Render() const;
		virtual void FixedUpdate();
		virtual void LateUpdate();

		template <typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			// check if component already exists
			if (T* component = GetComponent<T>())
			{
				return component;
			}
			auto component = std::make_shared<T>(std::forward<Args>(args)...);
			component->SetOwner(this);
			m_pComponents.push_back(component);
			return component.get();
		}

		template <typename T>
		T* GetComponent() const
		{
			for (const auto& component : m_pComponents)
			{
				if (auto comp = dynamic_cast<T*>(component.get()))
				{
					return comp;
				}
			}
			return nullptr;
		}

		template <typename T>
		void RemoveComponent()
		{
			for (size_t i = 0; i < m_pComponents.size(); ++i)
			{
				if (auto comp = dynamic_cast<T*>(m_pComponents[i].get()))
				{
					m_pComponents.erase(m_pComponents.begin() + i);
					return;
				}
			}
		}

		template <typename T>
		bool HasComponent() const
		{
			for (const auto& component : m_pComponents)
			{
				if (auto comp = dynamic_cast<T*>(component.get()))
				{
					return true;
				}
			}
			return false;
		}

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);

		bool hasParent() const { return m_pParent != nullptr; }

		/*void addObserver(std::shared_ptr<Observer> observer);
		void removeObserver(std::shared_ptr<Observer> observer);

		void Notify(const Event& event);*/
		

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	private:
		std::vector<std::shared_ptr<Component>> m_pComponents;
		std::vector<GameObject*> m_pChildren;
		GameObject* m_pParent = nullptr;

		void SetParent(GameObject* parent);

		//std::vector<std::shared_ptr<Observer>> m_Observers;
	};
}
