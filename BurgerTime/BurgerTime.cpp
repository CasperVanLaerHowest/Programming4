#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"

#include "Scene.h"
#include "GameObject.h"
#include "TextureRenderer.h"
#include "TransformComponent.h"
#include "TextRenderer.h"
#include "FpsComponent.h"
#include "RotatorComponent.h"
#include "InputManager.h"
#include "JumpCommand.h"
#include "MoveCommand.h"
#include <SDL_scancode.h>
#include "HealthComponent.h"
#include "TakeDamageCommand.h"
#include "AddScoreCommand.h"
#include "ScoreComponent.h"
#include <iostream>
#include "HealthObserver.h"
#include "ScoreObserver.h"


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& InputManager = dae::InputManager::GetInstance();
	auto& ResourceManager = dae::ResourceManager::GetInstance();

	/*auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<TextureRenderer>("background.tga");
	scene.Add(go);*/

	auto yo = std::make_shared<dae::GameObject>();
	yo->AddComponent<TextureRenderer>("logo.tga");
	yo->GetComponent<TransformComponent>()->SetPosition(216, 180, 0);
	scene.Add(yo);

	auto font = ResourceManager.LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<dae::GameObject>();
	to->AddComponent<TextRenderer>("Programming 4 Assignment", font);
	to->GetComponent<TransformComponent>()->SetPosition(80, 20, 0);
	scene.Add(to);

	auto so = std::make_shared<dae::GameObject>();
	so->AddComponent<TextRenderer>("FPS", font);
	so->AddComponent<FpsComponent>();
	scene.Add(so);

	auto character2 = std::make_shared<dae::GameObject>();
	character2->AddComponent<TextureRenderer>("character2.png");
	character2->GetComponent<TransformComponent>()->SetPosition(100, 200, 0);
	character2->AddComponent<HealthComponent>(3);
	character2->AddComponent<ScoreComponent>();
	//character2->AddComponent<RotatorComponent>(1.0f, 50.0f);
	scene.Add(character2);

	auto character1 = std::make_shared<dae::GameObject>();
	character1->AddComponent<TextureRenderer>("character1.png");
	character1->GetComponent<TransformComponent>()->SetPosition(50, 200, 0);
	character1->AddComponent<HealthComponent>(3);
	character1->AddComponent<ScoreComponent>();
	//character1->AddComponent<RotatorComponent>(0.5f, 50.0f);
	//character1->AddChild(character2.get());
	scene.Add(character1);

	auto font2 = ResourceManager.LoadFont("Lingua.otf", 12);

	auto Instruction1 = std::make_shared<dae::GameObject>();
	Instruction1->GetComponent<TransformComponent>()->SetPosition(5, 60, 0);
	Instruction1->AddComponent<TextRenderer>("Use WASD to move player1, T to inflict damage, Y to gain score", font2);
	scene.Add(Instruction1);

	auto Instruction2 = std::make_shared<dae::GameObject>();
	Instruction2->GetComponent<TransformComponent>()->SetPosition(5, 75, 0);
	Instruction2->AddComponent<TextRenderer>("Use D-PAD to move player2, X to inflict damage, C to gain score", font2);
	scene.Add(Instruction2);

	auto health1 = std::make_shared<dae::GameObject>();
	health1->GetComponent<TransformComponent>()->SetPosition(5, 100, 0);
	health1->AddComponent<TextRenderer>("Health: 3", font2);
	health1->AddComponent<HealthObserver>();
	scene.Add(health1);

	character1->GetComponent<HealthComponent>()->AddObserver(health1->GetComponent<HealthObserver>());

	auto score1 = std::make_shared<dae::GameObject>();
	score1->GetComponent<TransformComponent>()->SetPosition(5, 120, 0);
	score1->AddComponent<TextRenderer>("Score: 0", font2);
	score1->AddComponent<ScoreObserver>();
	scene.Add(score1);

	character1->GetComponent<ScoreComponent>()->AddObserver(score1->GetComponent<ScoreObserver>());

	auto health2 = std::make_shared<dae::GameObject>();
	health2->GetComponent<TransformComponent>()->SetPosition(5, 140, 0);
	health2->AddComponent<TextRenderer>("Health: 3", font2);
	health2->AddComponent<HealthObserver>();
	scene.Add(health2);

	character2->GetComponent<HealthComponent>()->AddObserver(health2->GetComponent<HealthObserver>());

	auto score2 = std::make_shared<dae::GameObject>();
	score2->GetComponent<TransformComponent>()->SetPosition(5, 160, 0);
	score2->AddComponent<TextRenderer>("Score: 0", font2);
	score2->AddComponent<ScoreObserver>();
	scene.Add(score2);

	character2->GetComponent<ScoreComponent>()->AddObserver(score2->GetComponent<ScoreObserver>());

	/*auto healthObserver1 = std::make_shared<HealthObserver>(health1);
	character1->addObserver(healthObserver1);

	auto healthObserver2 = std::make_shared<HealthObserver>(health2);
	character2->addObserver(healthObserver2);

	auto scoreObserver1 = std::make_shared<ScoreObserver>(score1);
	character1->addObserver(scoreObserver1);

	auto scoreObserver2 = std::make_shared<ScoreObserver>(score2);
	character2->addObserver(scoreObserver2);*/



	//--------------------------
	// BINDS
	//--------------------------

	InputManager.BindCommand(SDL_SCANCODE_SPACE, std::make_unique<JumpCommand>(character1));

	InputManager.BindCommand(SDL_SCANCODE_W, std::make_unique<MoveCommand>(character1, Direction::UP));
	InputManager.BindCommand(SDL_SCANCODE_S, std::make_unique<MoveCommand>(character1, Direction::DOWN));
	InputManager.BindCommand(SDL_SCANCODE_A, std::make_unique<MoveCommand>(character1, Direction::LEFT));
	InputManager.BindCommand(SDL_SCANCODE_D, std::make_unique<MoveCommand>(character1, Direction::RIGHT));

	InputManager.BindCommand(Inputs::DPAD_UP, std::make_unique<MoveCommand>(character2, Direction::UP));
	InputManager.BindCommand(Inputs::DPAD_DOWN, std::make_unique<MoveCommand>(character2, Direction::DOWN));
	InputManager.BindCommand(Inputs::DPAD_LEFT, std::make_unique<MoveCommand>(character2, Direction::LEFT));
	InputManager.BindCommand(Inputs::DPAD_RIGHT, std::make_unique<MoveCommand>(character2, Direction::RIGHT));

	InputManager.BindCommand(SDL_SCANCODE_T, std::make_unique<TakeDamageCommand>(character1));
	InputManager.BindCommand(SDL_SCANCODE_Y, std::make_unique<AddScoreCommand>(character1));

	InputManager.BindCommand(SDL_SCANCODE_X, std::make_unique<TakeDamageCommand>(character2));
	InputManager.BindCommand(SDL_SCANCODE_C, std::make_unique<AddScoreCommand>(character2));
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}