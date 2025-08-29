#pragma once
#include "Singleton.h"
#include <vector>
#include "GameObject.h"

namespace dae
{
	enum class TypeObject
	{
		PLATFORM,
		LADDER,
		WALL
	};

	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		void AddCollisionObject(std::shared_ptr<GameObject> object, TypeObject type);
		bool CheckBottomCollision(const std::shared_ptr<GameObject>& object, TypeObject type) const;
		bool CheckCollision(const std::shared_ptr<GameObject>& object, TypeObject type) const;
		float GetYCollision(const std::shared_ptr<GameObject>& object, TypeObject type) const;
	private:
		friend class Singleton<CollisionManager>;
		CollisionManager() = default;
		std::vector<std::shared_ptr<GameObject>> m_Platforms;
		std::vector<std::shared_ptr<GameObject>> m_Ladders;
		std::vector<std::shared_ptr<GameObject>> m_Walls;
	};

}


