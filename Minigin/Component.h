#pragma once
#include <string>

namespace dae
{

	class GameObject;

	class Component
	{
	public:
		virtual ~Component();
		virtual void Update();
		virtual void Render() const {}
		virtual void FixedUpdate() {}
		virtual void LateUpdate() {}

		void SetOwner(GameObject* owner) { m_pOwner = owner; }
		GameObject* GetOwner() const { return m_pOwner; }

	private:
		GameObject* m_pOwner = nullptr;
	};
}
