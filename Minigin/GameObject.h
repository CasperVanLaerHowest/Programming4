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
		//virtual void Render() const;

		//void SetTexture(const std::string& filename);
		//void SetPosition(float x, float y);

		void AddComponent(Component* pComponent);
		void RemoveComponent(const std::string& name);
		//Component* GetComponent(const std::string& name);
		bool HasComponent(const std::string& name) const;

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <typename T>
		T* GetComponent() {
			for (auto* component : m_pComponents) {
				T* derived = dynamic_cast<T*>(component);
				if (derived) {
					return derived;
				}
			}
			return nullptr;
		}

	private:
		std::vector<std::unique_ptr<Component>> m_pComponents{};
		//Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		//std::shared_ptr<Texture2D> m_texture{};
	};
}
