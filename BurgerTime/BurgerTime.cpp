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
#include "BoxCollisionComponent.h"
#include "CollisionManager.h"

// --- Function to bind all player commands ---
// This function encapsulates the command binding logic to keep the load function clean.
void bindCommands(std::shared_ptr<dae::GameObject> character1, std::shared_ptr<dae::GameObject> character2)
{
	auto& InputManager = dae::InputManager::GetInstance();

	// Player 1 Commands
	//InputManager.BindCommand(SDL_SCANCODE_SPACE, std::make_unique<JumpCommand>(character1));
	InputManager.BindCommand(SDL_SCANCODE_W, std::make_unique<MoveCommand>(character1, Direction::UP));
	InputManager.BindCommand(SDL_SCANCODE_S, std::make_unique<MoveCommand>(character1, Direction::DOWN));
	InputManager.BindCommand(SDL_SCANCODE_A, std::make_unique<MoveCommand>(character1, Direction::LEFT));
	InputManager.BindCommand(SDL_SCANCODE_D, std::make_unique<MoveCommand>(character1, Direction::RIGHT));

	InputManager.BindCommand(SDL_SCANCODE_T, std::make_unique<TakeDamageCommand>(character1));
	InputManager.BindCommand(SDL_SCANCODE_Y, std::make_unique<AddScoreCommand>(character1));

	// Player 2 Commands
	InputManager.BindCommand(Inputs::DPAD_UP, std::make_unique<MoveCommand>(character2, Direction::UP));
	InputManager.BindCommand(Inputs::DPAD_DOWN, std::make_unique<MoveCommand>(character2, Direction::DOWN));
	InputManager.BindCommand(Inputs::DPAD_LEFT, std::make_unique<MoveCommand>(character2, Direction::LEFT));
	InputManager.BindCommand(Inputs::DPAD_RIGHT, std::make_unique<MoveCommand>(character2, Direction::RIGHT));

	InputManager.BindCommand(SDL_SCANCODE_X, std::make_unique<TakeDamageCommand>(character2));
	InputManager.BindCommand(SDL_SCANCODE_C, std::make_unique<AddScoreCommand>(character2));
}

void loadLevel1(dae::Scene& scene) {
	// --- Load Level 1 Background ---
	auto background1 = std::make_shared<dae::GameObject>();
	background1->AddComponent<TextureRenderer>("Level1.png");
	background1->GetComponent<TransformComponent>()->SetPosition(110, 80, 0);
	scene.Add(background1);
}

void LoadGameText(dae::Scene& scene, std::shared_ptr<dae::Font> font)
{
	// --- 1UP Object ---
	auto oneUp = std::make_shared<dae::GameObject>();
	oneUp->GetComponent<TransformComponent>()->SetPosition(115, 5, 0);
	oneUp->AddComponent<TextRenderer>("1UP", font);
	scene.Add(oneUp);

	// --- HighScore Object ---
	auto HighScore = std::make_shared<dae::GameObject>();
	HighScore->GetComponent<TransformComponent>()->SetPosition(200, 5, 0);
	HighScore->AddComponent<TextRenderer>("HI-SCORE", font);
	scene.Add(HighScore);

	// --- Pepper Object ---
	auto pepper = std::make_shared<dae::GameObject>();
	pepper->GetComponent<TransformComponent>()->SetPosition(450, 5, 0);
	pepper->AddComponent<TextRenderer>("PEPPER", font);
	scene.Add(pepper);
}

void load()
{
	// --- Scene and Manager Setup ---
	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("Level1");
	auto& ResourceManager = dae::ResourceManager::GetInstance();
	auto& CollisionManager = dae::CollisionManager::GetInstance();

	// --- Font Loading ---
	auto font = ResourceManager.LoadFont("Lingua.otf", 36);
	auto font2 = ResourceManager.LoadFont("Lingua.otf", 12);
	auto font3 = ResourceManager.LoadFont("Lingua.otf", 24);

	// --- FPS Counter ---
	/*auto fpsCounter = std::make_shared<dae::GameObject>();
	fpsCounter->AddComponent<TextRenderer>("FPS", font);
	fpsCounter->AddComponent<FpsComponent>();
	scene.Add(fpsCounter);*/

	// --- Load Level 1 ---
	loadLevel1(scene1);
#pragma region ladders
	auto CollisionBoxLadder01 = std::make_shared<dae::GameObject>();
	CollisionBoxLadder01->AddComponent<BoxCollisionComponent>(22, 162); // 160 + 2 = 162
	CollisionBoxLadder01->GetComponent<TransformComponent>()->SetPosition(115, 232, 0);
	CollisionManager.AddCollisionObject(CollisionBoxLadder01, dae::TypeObject::LADDER);

	auto CollisionBoxLadder02 = std::make_shared<dae::GameObject>();
	CollisionBoxLadder02->AddComponent<BoxCollisionComponent>(22, 66); // 64 + 2 = 66
	CollisionBoxLadder02->GetComponent<TransformComponent>()->SetPosition(115, 104, 0);
	CollisionManager.AddCollisionObject(CollisionBoxLadder02, dae::TypeObject::LADDER);

	auto CollisionBoxLadder03 = std::make_shared<dae::GameObject>();
	CollisionBoxLadder03->AddComponent<BoxCollisionComponent>(22, 162); // 160 + 2 = 162
	CollisionBoxLadder03->GetComponent<TransformComponent>()->SetPosition(163, 168, 0);
	CollisionManager.AddCollisionObject(CollisionBoxLadder03, dae::TypeObject::LADDER);

	auto CollisionBoxLadder04 = std::make_shared<dae::GameObject>();
	CollisionBoxLadder04->AddComponent<BoxCollisionComponent>(22, 290); // 288 + 2 = 290
	CollisionBoxLadder04->GetComponent<TransformComponent>()->SetPosition(211, 104, 0);
	CollisionManager.AddCollisionObject(CollisionBoxLadder04, dae::TypeObject::LADDER);

	auto CollisionBoxLadder05 = std::make_shared<dae::GameObject>();
	CollisionBoxLadder05->AddComponent<BoxCollisionComponent>(22, 98); // 96 + 2 = 98
	CollisionBoxLadder05->GetComponent<TransformComponent>()->SetPosition(259, 104, 0);
	CollisionManager.AddCollisionObject(CollisionBoxLadder05, dae::TypeObject::LADDER);

	auto CollisionBoxLadder06 = std::make_shared<dae::GameObject>();
	CollisionBoxLadder06->AddComponent<BoxCollisionComponent>(22, 290); // 288 + 2 = 290
	CollisionBoxLadder06->GetComponent<TransformComponent>()->SetPosition(307, 104, 0);
	CollisionManager.AddCollisionObject(CollisionBoxLadder06, dae::TypeObject::LADDER);

	auto CollisionBoxLadder07 = std::make_shared<dae::GameObject>();
	CollisionBoxLadder07->AddComponent<BoxCollisionComponent>(22, 98); // 96 + 2 = 98
	CollisionBoxLadder07->GetComponent<TransformComponent>()->SetPosition(355, 168, 0);
	CollisionManager.AddCollisionObject(CollisionBoxLadder07, dae::TypeObject::LADDER);

	auto CollisionBoxLadder08 = std::make_shared<dae::GameObject>();
	CollisionBoxLadder08->AddComponent<BoxCollisionComponent>(22, 290); // 288 + 2 = 290
	CollisionBoxLadder08->GetComponent<TransformComponent>()->SetPosition(403, 104, 0);
	CollisionManager.AddCollisionObject(CollisionBoxLadder08, dae::TypeObject::LADDER);

	auto CollisionBoxLadder09 = std::make_shared<dae::GameObject>();
	CollisionBoxLadder09->AddComponent<BoxCollisionComponent>(22, 162); // 160 + 2 = 162
	CollisionBoxLadder09->GetComponent<TransformComponent>()->SetPosition(451, 232, 0);
	CollisionManager.AddCollisionObject(CollisionBoxLadder09, dae::TypeObject::LADDER);

	auto CollisionBoxLadder10 = std::make_shared<dae::GameObject>();
	CollisionBoxLadder10->AddComponent<BoxCollisionComponent>(22, 98); // 96 + 2 = 98
	CollisionBoxLadder10->GetComponent<TransformComponent>()->SetPosition(499, 296, 0);
	CollisionManager.AddCollisionObject(CollisionBoxLadder10, dae::TypeObject::LADDER);

	auto CollisionBoxLadder11 = std::make_shared<dae::GameObject>();
	CollisionBoxLadder11->AddComponent<BoxCollisionComponent>(22, 130); // 128 + 2 = 130
	CollisionBoxLadder11->GetComponent<TransformComponent>()->SetPosition(499, 104, 0);
	CollisionManager.AddCollisionObject(CollisionBoxLadder11, dae::TypeObject::LADDER);
#pragma endregion ladders
#pragma region platforms

	auto CollisionBoxPlatform01 = std::make_shared<dae::GameObject>();
	CollisionBoxPlatform01->AddComponent<BoxCollisionComponent>(416, 4); // Switched
	CollisionBoxPlatform01->GetComponent<TransformComponent>()->SetPosition(110, 398, 0);
	CollisionManager.AddCollisionObject(CollisionBoxPlatform01, dae::TypeObject::PLATFORM);
	scene1.Add(CollisionBoxPlatform01);

	auto CollisionBoxPlatform02 = std::make_shared<dae::GameObject>();
	CollisionBoxPlatform02->AddComponent<BoxCollisionComponent>(320, 4); // Switched
	CollisionBoxPlatform02->GetComponent<TransformComponent>()->SetPosition(110, 334, 0);
	CollisionManager.AddCollisionObject(CollisionBoxPlatform02, dae::TypeObject::PLATFORM);
	scene1.Add(CollisionBoxPlatform02);

	auto CollisionBoxPlatform03 = std::make_shared<dae::GameObject>();
	CollisionBoxPlatform03->AddComponent<BoxCollisionComponent>(128, 4); // Switched
	CollisionBoxPlatform03->GetComponent<TransformComponent>()->SetPosition(398, 302, 0);
	CollisionManager.AddCollisionObject(CollisionBoxPlatform03, dae::TypeObject::PLATFORM);
	scene1.Add(CollisionBoxPlatform03);

	auto CollisionBoxPlatform04 = std::make_shared<dae::GameObject>();
	CollisionBoxPlatform04->AddComponent<BoxCollisionComponent>(224, 4); // Switched
	CollisionBoxPlatform04->GetComponent<TransformComponent>()->SetPosition(206, 270, 0);
	CollisionManager.AddCollisionObject(CollisionBoxPlatform04, dae::TypeObject::PLATFORM);
	scene1.Add(CollisionBoxPlatform04);

	auto CollisionBoxPlatform05 = std::make_shared<dae::GameObject>();
	CollisionBoxPlatform05->AddComponent<BoxCollisionComponent>(128, 4); // Switched
	CollisionBoxPlatform05->GetComponent<TransformComponent>()->SetPosition(110, 238, 0);
	CollisionManager.AddCollisionObject(CollisionBoxPlatform05, dae::TypeObject::PLATFORM);
	scene1.Add(CollisionBoxPlatform05);

	auto CollisionBoxPlatform06 = std::make_shared<dae::GameObject>();
	CollisionBoxPlatform06->AddComponent<BoxCollisionComponent>(128, 4); // Switched
	CollisionBoxPlatform06->GetComponent<TransformComponent>()->SetPosition(398, 238, 0);
	CollisionManager.AddCollisionObject(CollisionBoxPlatform06, dae::TypeObject::PLATFORM);
	scene1.Add(CollisionBoxPlatform06);

	auto CollisionBoxPlatform07 = std::make_shared<dae::GameObject>();
	CollisionBoxPlatform07->AddComponent<BoxCollisionComponent>(128, 4); // Switched
	CollisionBoxPlatform07->GetComponent<TransformComponent>()->SetPosition(206, 206, 0);
	CollisionManager.AddCollisionObject(CollisionBoxPlatform07, dae::TypeObject::PLATFORM);
	scene1.Add(CollisionBoxPlatform07);

	auto CollisionBoxPlatform08 = std::make_shared<dae::GameObject>();
	CollisionBoxPlatform08->AddComponent<BoxCollisionComponent>(128, 4); // Switched
	CollisionBoxPlatform08->GetComponent<TransformComponent>()->SetPosition(110, 174, 0);
	CollisionManager.AddCollisionObject(CollisionBoxPlatform08, dae::TypeObject::PLATFORM);
	scene1.Add(CollisionBoxPlatform08);

	auto CollisionBoxPlatform09 = std::make_shared<dae::GameObject>();
	CollisionBoxPlatform09->AddComponent<BoxCollisionComponent>(224, 4); // Switched
	CollisionBoxPlatform09->GetComponent<TransformComponent>()->SetPosition(302, 174, 0);
	CollisionManager.AddCollisionObject(CollisionBoxPlatform09, dae::TypeObject::PLATFORM);
	scene1.Add(CollisionBoxPlatform09);

	auto CollisionBoxPlatform10 = std::make_shared<dae::GameObject>();
	CollisionBoxPlatform10->AddComponent<BoxCollisionComponent>(416, 4); // Switched
	CollisionBoxPlatform10->GetComponent<TransformComponent>()->SetPosition(110, 110, 0);
	CollisionManager.AddCollisionObject(CollisionBoxPlatform10, dae::TypeObject::PLATFORM);
	scene1.Add(CollisionBoxPlatform10);

#pragma endregion platforms
	// --- Load Game Text ---
	LoadGameText(scene1, font3);
	

	// --- Player 2 Setup ---
	auto character2 = std::make_shared<dae::GameObject>();
	character2->AddComponent<TextureRenderer>("character2.png");
	character2->GetComponent<TransformComponent>()->SetPosition(0, 0, 0);
	character2->AddComponent<HealthComponent>(3);
	character2->AddComponent<ScoreComponent>();
	character2->AddComponent<BoxCollisionComponent>(20, 20);
	scene1.Add(character2);

	// --- Player 1 Setup ---
	auto character1 = std::make_shared<dae::GameObject>();
	character1->AddComponent<TextureRenderer>("character1.png");
	character1->GetComponent<TransformComponent>()->SetPosition(150, 378, 0);
	character1->AddComponent<HealthComponent>(3);
	character1->AddComponent<ScoreComponent>();
	character1->AddComponent<BoxCollisionComponent>(16, 16);
	scene1.Add(character1);

	// --- UI Instructions ---
	/*auto instruction1 = std::make_shared<dae::GameObject>();
	instruction1->GetComponent<TransformComponent>()->SetPosition(5, 60, 0);
	instruction1->AddComponent<TextRenderer>("Use WASD to move player1, T to inflict damage, Y to gain score", font2);
	scene.Add(instruction1);

	auto instruction2 = std::make_shared<dae::GameObject>();
	instruction2->GetComponent<TransformComponent>()->SetPosition(5, 75, 0);
	instruction2->AddComponent<TextRenderer>("Use D-PAD to move player2, X to inflict damage, C to gain score", font2);
	scene.Add(instruction2);*/

	// --- Player 1 UI Observers ---
	/*auto health1 = std::make_shared<dae::GameObject>();
	health1->GetComponent<TransformComponent>()->SetPosition(5, 100, 0);
	health1->AddComponent<TextRenderer>("Health: 3", font2);
	health1->AddComponent<HealthObserver>();
	character1->GetComponent<HealthComponent>()->AddObserver(health1->GetComponent<HealthObserver>());
	scene.Add(health1);*/

	auto score1 = std::make_shared<dae::GameObject>();
	score1->GetComponent<TransformComponent>()->SetPosition(115, 30, 0);
	score1->AddComponent<TextRenderer>("0", font3);
	score1->AddComponent<ScoreObserver>();
	character1->GetComponent<ScoreComponent>()->AddObserver(score1->GetComponent<ScoreObserver>());
	scene1.Add(score1);

	// --- Player 2 UI Observers ---
	/*auto health2 = std::make_shared<dae::GameObject>();
	health2->GetComponent<TransformComponent>()->SetPosition(5, 140, 0);
	health2->AddComponent<TextRenderer>("Health: 3", font2);
	health2->AddComponent<HealthObserver>();
	character2->GetComponent<HealthComponent>()->AddObserver(health2->GetComponent<HealthObserver>());
	scene.Add(health2);*/

	/*auto score2 = std::make_shared<dae::GameObject>();
	score2->GetComponent<TransformComponent>()->SetPosition(5, 160, 0);
	score2->AddComponent<TextRenderer>("Score: 0", font2);
	score2->AddComponent<ScoreObserver>();
	character2->GetComponent<ScoreComponent>()->AddObserver(score2->GetComponent<ScoreObserver>());
	scene.Add(score2);*/

	// --- Platform Setup ---


	
	// --- Bind All Commands ---
	bindCommands(character1, character2);

	
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}