#pragma once
#include <memory>
#include <vector>
#include "Component.h"
#include <unordered_map>
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

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	private:
		std::vector<std::shared_ptr<Component>> m_pComponents;
	};
}
