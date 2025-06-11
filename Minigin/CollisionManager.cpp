#include "CollisionManager.h"
#include "GameObject.h"
#include "../BurgerTime/BoxCollisionComponent.h"
#include "TransformComponent.h"

void dae::CollisionManager::AddCollisionObject(std::shared_ptr<GameObject> object, TypeObject type)
{
	if (!object)
		return;

	switch (type)
	{
	case TypeObject::PLATFORM:
		m_Platforms.push_back(object);
		break;
	case TypeObject::LADDER:
		m_Ladders.push_back(object);
		break;
	case TypeObject::WALL:
		m_Walls.push_back(object);
		break;
	default:
		break;
	}
}

bool dae::CollisionManager::CheckBottomCollision(const std::shared_ptr<GameObject>& object, TypeObject type) const
{
	if (!object)
		return false;

	const auto& collisionBox = object->GetComponent<BoxCollisionComponent>();
	const auto& transform = object->GetComponent<TransformComponent>();

	if (!collisionBox || !transform)
		return false;

	const auto& transformPos = transform->GetPosition();
	float characterLeftX = transformPos.x;
	float characterRightX = transformPos.x + collisionBox->GetWidth();
	float characterBottomY = transformPos.y + collisionBox->GetHeight();

	float checkDistanceP = 7.f; 
	float checkDistanceL = 19.f;

	switch (type)
	{
	case dae::TypeObject::PLATFORM:
		for (const auto& platform : m_Platforms)
		{
			const auto& platformBox = platform->GetComponent<BoxCollisionComponent>();
			const auto& platformTransform = platform->GetComponent<TransformComponent>()->GetPosition();

			float platformLeftX = platformTransform.x;
			float platformRightX = platformTransform.x + platformBox->GetWidth();
			float platformTopY = platformTransform.y;
			float platformBottomY = platformTransform.y + platformBox->GetHeight(); // Assuming y increases downwards

			// 1. Check for horizontal overlap
			bool horizontalOverlap = (characterRightX > platformLeftX && characterLeftX < platformRightX);
			bool verticalOverlap = (characterBottomY + checkDistanceP >= platformTopY && characterBottomY < platformBottomY);


			if (horizontalOverlap && verticalOverlap)
			{
				return true;
			}
		}
		break;
	case dae::TypeObject::LADDER:
		for (const auto& ladder : m_Ladders)
		{
			const auto& ladderBox = ladder->GetComponent<BoxCollisionComponent>();
			const auto& ladderTransform = ladder->GetComponent<TransformComponent>()->GetPosition();

			float ladderLeftX = ladderTransform.x;
			float ladderRightX = ladderTransform.x + ladderBox->GetWidth();
			float ladderTopY = ladderTransform.y;
			float ladderBottomY = ladderTransform.y + ladderBox->GetHeight(); // Assuming y increases downwards

			// Define how far below the character we want to check for ladder presence
			// This value determines how much "leeway" the character has to detect a ladder below them for climbing down.
 // Adjust this value as needed

			// 1. Check for horizontal overlap between character and ladder
			bool horizontalOverlap = (characterRightX > ladderLeftX && characterLeftX < ladderRightX);

			// 2. Check for vertical overlap between character and ladder
			// We're checking if the character's *current top edge* (transformPos.y)
			// OR a point slightly below their top edge (transformPos.y + checkDistanceL)
			// is vertically overlapping with the ladder.
			bool verticalOverlap = (transformPos.y + checkDistanceL < ladderBottomY && characterBottomY > ladderTopY);

			if (horizontalOverlap && verticalOverlap)
			{
				return true;
			}
		}
		break;
	default:
		break;
	}
	return false;
}

bool dae::CollisionManager::CheckCollision(const std::shared_ptr<GameObject>& object, TypeObject type) const
{
	if (!object)
		return false;

	const auto& collisionBox = object->GetComponent<BoxCollisionComponent>();
	const auto& transform = object->GetComponent<TransformComponent>();

	if (!collisionBox || !transform)
		return false;

	const auto& transformPos = transform->GetPosition();
	float characterLeftX = transformPos.x;
	float characterRightX = transformPos.x + collisionBox->GetWidth();
	float characterTopY = transformPos.y;
	float characterBottomY = transformPos.y + collisionBox->GetHeight();

	switch (type)
	{
	case dae::TypeObject::LADDER:
		for (const auto& ladder : m_Ladders)
		{
			const auto& ladderBox = ladder->GetComponent<BoxCollisionComponent>();
			const auto& ladderTransform = ladder->GetComponent<TransformComponent>()->GetPosition();

			float ladderLeftX = ladderTransform.x;
			float ladderRightX = ladderTransform.x + ladderBox->GetWidth();
			float ladderTopY = ladderTransform.y;
			float ladderBottomY = ladderTransform.y + ladderBox->GetHeight(); // Assuming y increases downwards

			// 1. Check for horizontal overlap between character and ladder
			bool horizontalOverlap = (characterRightX > ladderLeftX && characterLeftX < ladderRightX);

			// 2. Check for vertical overlap between character and ladder (general overlap)
			// Character's top must be above ladder's bottom
			// Character's bottom must be below ladder's top
			bool verticalOverlap = (characterTopY < ladderBottomY && characterBottomY - 2.f > ladderTopY);

			if (horizontalOverlap && verticalOverlap)
			{
				return true;
			}
		}
		break;
	default:
		// If 'type' is not LADDER, or any other unhandled type, return false.
		// PLATFORM checks are no longer included in this function.
		break;
	}
	return false;
}
