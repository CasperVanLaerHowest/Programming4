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
	//loadLevel1(scene1);
	
	// --- Load Game Text ---
	LoadGameText(scene1, font3);
	

	// --- Player 2 Setup ---
	auto character2 = std::make_shared<dae::GameObject>();
	character2->AddComponent<TextureRenderer>("character2.png");
	character2->GetComponent<TransformComponent>()->SetPosition(100, 200, 0);
	character2->AddComponent<HealthComponent>(3);
	character2->AddComponent<ScoreComponent>();
	scene1.Add(character2);

	// --- Player 1 Setup ---
	auto character1 = std::make_shared<dae::GameObject>();
	character1->AddComponent<TextureRenderer>("character1.png");
	character1->GetComponent<TransformComponent>()->SetPosition(50, 200, 0);
	character1->AddComponent<HealthComponent>(3);
	character1->AddComponent<ScoreComponent>();
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

#pragma region Platform row 1
	//ladders
	auto ladder1 = std::make_shared<dae::GameObject>();
	ladder1->AddComponent<BoxCollisionComponent>(20, 32);
	ladder1->GetComponent<TransformComponent>()->SetPosition(115, 362, 0);
	ladder1->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder1);

	auto ladder2 = std::make_shared<dae::GameObject>();
	ladder2->AddComponent<BoxCollisionComponent>(20, 32);
	ladder2->GetComponent<TransformComponent>()->SetPosition(115, 330, 0);
	ladder2->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder2);

	auto ladder3 = std::make_shared<dae::GameObject>();
	ladder3->AddComponent<BoxCollisionComponent>(20, 32);
	ladder3->GetComponent<TransformComponent>()->SetPosition(115, 298, 0);
	ladder3->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder3);

	auto ladder4 = std::make_shared<dae::GameObject>();
	ladder4->AddComponent<BoxCollisionComponent>(20, 32);
	ladder4->GetComponent<TransformComponent>()->SetPosition(115, 266, 0);
	ladder4->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder4);

	auto ladder5 = std::make_shared<dae::GameObject>();
	ladder5->AddComponent<BoxCollisionComponent>(20, 32);
	ladder5->GetComponent<TransformComponent>()->SetPosition(115, 234, 0);
	ladder5->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder5);

	auto ladder6 = std::make_shared<dae::GameObject>();
	ladder6->AddComponent<BoxCollisionComponent>(20, 32);
	ladder6->GetComponent<TransformComponent>()->SetPosition(115, 138, 0);
	ladder6->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder6);

	auto ladder7 = std::make_shared<dae::GameObject>();
	ladder7->AddComponent<BoxCollisionComponent>(20, 32);
	ladder7->GetComponent<TransformComponent>()->SetPosition(115, 106, 0);
	ladder7->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder7);

	//platforms
	auto platformL11 = std::make_shared<dae::GameObject>();
	platformL11->AddComponent<BoxCollisionComponent>(32, 20);
	platformL11->GetComponent<TransformComponent>()->SetPosition(110, 394, 0);
	platformL11->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL11);

	auto platformL21 = std::make_shared<dae::GameObject>();
	platformL21->AddComponent<BoxCollisionComponent>(32, 20);
	platformL21->GetComponent<TransformComponent>()->SetPosition(110, 330, 0);
	platformL21->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL21);

	auto platformL31 = std::make_shared<dae::GameObject>();
	platformL31->AddComponent<BoxCollisionComponent>(32, 20);
	platformL31->GetComponent<TransformComponent>()->SetPosition(110, 234, 0);
	platformL31->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL31);

	auto platformL41 = std::make_shared<dae::GameObject>();
	platformL41->AddComponent<BoxCollisionComponent>(32, 20);
	platformL41->GetComponent<TransformComponent>()->SetPosition(110, 170, 0);
	platformL41->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL41);

	auto platformL51 = std::make_shared<dae::GameObject>();
	platformL51->AddComponent<BoxCollisionComponent>(32, 20);
	platformL51->GetComponent<TransformComponent>()->SetPosition(110, 106, 0);
	platformL51->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL51);

	

#pragma endregion Platform row 1
#pragma region Platform row 2-3

	auto ladder31 = std::make_shared<dae::GameObject>();
	ladder31->AddComponent<BoxCollisionComponent>(20, 32);
	ladder31->GetComponent<TransformComponent>()->SetPosition(163, 298, 0);
	ladder31->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder31);

	auto ladder41 = std::make_shared<dae::GameObject>();
	ladder41->AddComponent<BoxCollisionComponent>(20, 32);
	ladder41->GetComponent<TransformComponent>()->SetPosition(163, 266, 0);
	ladder41->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder41);

	auto ladder51 = std::make_shared<dae::GameObject>();
	ladder51->AddComponent<BoxCollisionComponent>(20, 32);
	ladder51->GetComponent<TransformComponent>()->SetPosition(163, 234, 0);
	ladder51->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder51);

	auto ladder61 = std::make_shared<dae::GameObject>();
	ladder61->AddComponent<BoxCollisionComponent>(20, 32);
	ladder61->GetComponent<TransformComponent>()->SetPosition(163, 202, 0);
	ladder61->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder61);

	auto ladder71 = std::make_shared<dae::GameObject>();
	ladder71->AddComponent<BoxCollisionComponent>(20, 32);
	ladder71->GetComponent<TransformComponent>()->SetPosition(163, 170, 0);
	ladder71->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder71);

#pragma endregion Platform row 2-3
#pragma region Platform row 2

	auto platformR11 = std::make_shared<dae::GameObject>();
	platformR11->AddComponent<BoxCollisionComponent>(100, 20);
	platformR11->GetComponent<TransformComponent>()->SetPosition(142, 394, 0);
	platformR11->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR11);

	auto platformR21 = std::make_shared<dae::GameObject>();
	platformR21->AddComponent<BoxCollisionComponent>(100, 20);
	platformR21->GetComponent<TransformComponent>()->SetPosition(142, 330, 0);
	platformR21->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR21);

	auto platformR31 = std::make_shared<dae::GameObject>();
	platformR31->AddComponent<BoxCollisionComponent>(100, 20);
	platformR31->GetComponent<TransformComponent>()->SetPosition(142, 234, 0);
	platformR31->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR31);

	auto platformR41 = std::make_shared<dae::GameObject>();
	platformR41->AddComponent<BoxCollisionComponent>(100, 20);
	platformR41->GetComponent<TransformComponent>()->SetPosition(142, 170, 0);
	platformR41->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR41);

	auto platformR51 = std::make_shared<dae::GameObject>();
	platformR51->AddComponent<BoxCollisionComponent>(100, 20);
	platformR51->GetComponent<TransformComponent>()->SetPosition(142, 106, 0);
	platformR51->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR51);

#pragma endregion Platform row 2
#pragma region Platform row 3

	auto platformR12 = std::make_shared<dae::GameObject>();
	platformR12->AddComponent<BoxCollisionComponent>(100, 20);
	platformR12->GetComponent<TransformComponent>()->SetPosition(174, 394, 0);
	platformR12->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR12);

	auto platformR22 = std::make_shared<dae::GameObject>();
	platformR22->AddComponent<BoxCollisionComponent>(100, 20);
	platformR22->GetComponent<TransformComponent>()->SetPosition(174, 330, 0);
	platformR22->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR22);

	auto platformR32 = std::make_shared<dae::GameObject>();
	platformR32->AddComponent<BoxCollisionComponent>(100, 20);
	platformR32->GetComponent<TransformComponent>()->SetPosition(174, 234, 0);
	platformR32->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR32);

	auto platformR42 = std::make_shared<dae::GameObject>();
	platformR42->AddComponent<BoxCollisionComponent>(100, 20);
	platformR42->GetComponent<TransformComponent>()->SetPosition(174, 170, 0);
	platformR42->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR42);

	auto platformR52 = std::make_shared<dae::GameObject>();
	platformR52->AddComponent<BoxCollisionComponent>(100, 20);
	platformR52->GetComponent<TransformComponent>()->SetPosition(174, 106, 0);
	platformR52->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR52);

#pragma endregion Platform row 3
#pragma region Platform row 4

	//ladders
	auto ladder12 = std::make_shared<dae::GameObject>();
	ladder12->AddComponent<BoxCollisionComponent>(20, 32);
	ladder12->GetComponent<TransformComponent>()->SetPosition(211, 362, 0);
	ladder12->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder12);

	auto ladder22 = std::make_shared<dae::GameObject>();
	ladder22->AddComponent<BoxCollisionComponent>(20, 32);
	ladder22->GetComponent<TransformComponent>()->SetPosition(211, 330, 0);
	ladder22->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder22);

	auto ladder32 = std::make_shared<dae::GameObject>();
	ladder32->AddComponent<BoxCollisionComponent>(20, 32);
	ladder32->GetComponent<TransformComponent>()->SetPosition(211, 298, 0);
	ladder32->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder32);

	auto ladder42 = std::make_shared<dae::GameObject>();
	ladder42->AddComponent<BoxCollisionComponent>(20, 32);
	ladder42->GetComponent<TransformComponent>()->SetPosition(211, 266, 0);
	ladder42->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder42);

	auto ladder52 = std::make_shared<dae::GameObject>();
	ladder52->AddComponent<BoxCollisionComponent>(20, 32);
	ladder52->GetComponent<TransformComponent>()->SetPosition(211, 234, 0);
	ladder52->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder52);

	auto ladder62 = std::make_shared<dae::GameObject>();
	ladder62->AddComponent<BoxCollisionComponent>(20, 32);
	ladder62->GetComponent<TransformComponent>()->SetPosition(211, 202, 0);
	ladder62->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder62);

	auto ladder72 = std::make_shared<dae::GameObject>();
	ladder72->AddComponent<BoxCollisionComponent>(20, 32);
	ladder72->GetComponent<TransformComponent>()->SetPosition(211, 170, 0);
	ladder72->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder72);

	auto ladder82 = std::make_shared<dae::GameObject>();
	ladder82->AddComponent<BoxCollisionComponent>(20, 32);
	ladder82->GetComponent<TransformComponent>()->SetPosition(211, 138, 0);
	ladder82->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder82);

	auto ladder92 = std::make_shared<dae::GameObject>();
	ladder92->AddComponent<BoxCollisionComponent>(20, 32);
	ladder92->GetComponent<TransformComponent>()->SetPosition(211, 106, 0);
	ladder92->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder92);

	//platforms
	auto platformL12 = std::make_shared<dae::GameObject>();
	platformL12->AddComponent<BoxCollisionComponent>(100, 20);
	platformL12->GetComponent<TransformComponent>()->SetPosition(206, 394, 0);
	platformL12->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL12);

	auto platformL22 = std::make_shared<dae::GameObject>();
	platformL22->AddComponent<BoxCollisionComponent>(100, 20);
	platformL22->GetComponent<TransformComponent>()->SetPosition(206, 330, 0);
	platformL22->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL22);

	auto platformL32 = std::make_shared<dae::GameObject>();
	platformL32->AddComponent<BoxCollisionComponent>(100, 20);
	platformL32->GetComponent<TransformComponent>()->SetPosition(206, 266, 0);
	platformL32->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL32);

	auto platformL42 = std::make_shared<dae::GameObject>();
	platformL42->AddComponent<BoxCollisionComponent>(100, 20);
	platformL42->GetComponent<TransformComponent>()->SetPosition(206, 234, 0);
	platformL42->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL42);

	auto platformL52 = std::make_shared<dae::GameObject>();
	platformL52->AddComponent<BoxCollisionComponent>(100, 20);
	platformL52->GetComponent<TransformComponent>()->SetPosition(206, 202, 0);
	platformL52->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL52);

	auto platformL62 = std::make_shared<dae::GameObject>();
	platformL62->AddComponent<BoxCollisionComponent>(100, 20);
	platformL62->GetComponent<TransformComponent>()->SetPosition(206, 170, 0);
	platformL62->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL62);

	auto platformL72 = std::make_shared<dae::GameObject>();
	platformL72->AddComponent<BoxCollisionComponent>(100, 20);
	platformL72->GetComponent<TransformComponent>()->SetPosition(206, 106, 0);
	platformL72->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL72);

#pragma endregion Platform row 4
#pragma region Platform row 5-6

	auto ladder13 = std::make_shared<dae::GameObject>();
	ladder13->AddComponent<BoxCollisionComponent>(20, 32);
	ladder13->GetComponent<TransformComponent>()->SetPosition(259, 170, 0);
	ladder13->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder13);

	auto ladder23 = std::make_shared<dae::GameObject>();
	ladder23->AddComponent<BoxCollisionComponent>(20, 32);
	ladder23->GetComponent<TransformComponent>()->SetPosition(259, 138, 0);
	ladder23->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder23);

	auto ladder33 = std::make_shared<dae::GameObject>();
	ladder33->AddComponent<BoxCollisionComponent>(20, 32);
	ladder33->GetComponent<TransformComponent>()->SetPosition(259, 106, 0);
	ladder33->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder33);

#pragma endregion Platform row 5-6
#pragma region Platform row 5

	auto platformR13 = std::make_shared<dae::GameObject>();
	platformR13->AddComponent<BoxCollisionComponent>(100, 20);
	platformR13->GetComponent<TransformComponent>()->SetPosition(238, 394, 0);
	platformR13->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR13);

	auto platformR23 = std::make_shared<dae::GameObject>();
	platformR23->AddComponent<BoxCollisionComponent>(100, 20);
	platformR23->GetComponent<TransformComponent>()->SetPosition(238, 330, 0);
	platformR23->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR23);

	auto platformR33 = std::make_shared<dae::GameObject>();
	platformR33->AddComponent<BoxCollisionComponent>(100, 20);
	platformR33->GetComponent<TransformComponent>()->SetPosition(238, 266, 0);
	platformR33->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR33);

	auto platformR43 = std::make_shared<dae::GameObject>();
	platformR43->AddComponent<BoxCollisionComponent>(100, 20);
	platformR43->GetComponent<TransformComponent>()->SetPosition(238, 202, 0);
	platformR43->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR43);

	auto platformR53 = std::make_shared<dae::GameObject>();
	platformR53->AddComponent<BoxCollisionComponent>(100, 20);
	platformR53->GetComponent<TransformComponent>()->SetPosition(238, 106, 0);
	platformR53->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR53);


#pragma endregion Platform row 5
#pragma region Platform row 6

	auto platformR14 = std::make_shared<dae::GameObject>();
	platformR14->AddComponent<BoxCollisionComponent>(100, 20);
	platformR14->GetComponent<TransformComponent>()->SetPosition(270, 394, 0);
	platformR14->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR14);

	auto platformR24 = std::make_shared<dae::GameObject>();
	platformR24->AddComponent<BoxCollisionComponent>(100, 20);
	platformR24->GetComponent<TransformComponent>()->SetPosition(270, 330, 0);
	platformR24->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR24);

	auto platformR34 = std::make_shared<dae::GameObject>();
	platformR34->AddComponent<BoxCollisionComponent>(100, 20);
	platformR34->GetComponent<TransformComponent>()->SetPosition(270, 266, 0);
	platformR34->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR34);

	auto platformR44 = std::make_shared<dae::GameObject>();
	platformR44->AddComponent<BoxCollisionComponent>(100, 20);
	platformR44->GetComponent<TransformComponent>()->SetPosition(270, 202, 0);
	platformR44->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR44);

	auto platformR54 = std::make_shared<dae::GameObject>();
	platformR54->AddComponent<BoxCollisionComponent>(100, 20);
	platformR54->GetComponent<TransformComponent>()->SetPosition(270, 106, 0);
	platformR54->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR54);

#pragma endregion Platform row 6
#pragma region Platform row 7
	//ladders
	auto ladder14 = std::make_shared<dae::GameObject>();
	ladder14->AddComponent<BoxCollisionComponent>(20, 32);
	ladder14->GetComponent<TransformComponent>()->SetPosition(307, 362, 0);
	ladder14->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder14);

	auto ladder24 = std::make_shared<dae::GameObject>();
	ladder24->AddComponent<BoxCollisionComponent>(20, 32);
	ladder24->GetComponent<TransformComponent>()->SetPosition(307, 330, 0);
	ladder24->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder24);

	auto ladder34 = std::make_shared<dae::GameObject>();
	ladder34->AddComponent<BoxCollisionComponent>(20, 32);
	ladder34->GetComponent<TransformComponent>()->SetPosition(307, 298, 0);
	ladder34->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder34);

	auto ladder44 = std::make_shared<dae::GameObject>();
	ladder44->AddComponent<BoxCollisionComponent>(20, 32);
	ladder44->GetComponent<TransformComponent>()->SetPosition(307, 266, 0);
	ladder44->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder44);

	auto ladder54 = std::make_shared<dae::GameObject>();
	ladder54->AddComponent<BoxCollisionComponent>(20, 32);
	ladder54->GetComponent<TransformComponent>()->SetPosition(307, 234, 0);
	ladder54->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder54);

	auto ladder64 = std::make_shared<dae::GameObject>();
	ladder64->AddComponent<BoxCollisionComponent>(20, 32);
	ladder64->GetComponent<TransformComponent>()->SetPosition(307, 202, 0);
	ladder64->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder64);

	auto ladder74 = std::make_shared<dae::GameObject>();
	ladder74->AddComponent<BoxCollisionComponent>(20, 32);
	ladder74->GetComponent<TransformComponent>()->SetPosition(307, 170, 0);
	ladder74->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder74);

	auto ladder84 = std::make_shared<dae::GameObject>();
	ladder84->AddComponent<BoxCollisionComponent>(20, 32);
	ladder84->GetComponent<TransformComponent>()->SetPosition(307, 138, 0);
	ladder84->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder84);

	auto ladder94 = std::make_shared<dae::GameObject>();
	ladder94->AddComponent<BoxCollisionComponent>(20, 32);
	ladder94->GetComponent<TransformComponent>()->SetPosition(307, 106, 0);
	ladder94->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder94);
	
	//platform
	auto platformL13 = std::make_shared<dae::GameObject>();
	platformL13->AddComponent<BoxCollisionComponent>(100, 20);
	platformL13->GetComponent<TransformComponent>()->SetPosition(302, 394, 0);
	platformL13->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL13);

	auto platformL23 = std::make_shared<dae::GameObject>();
	platformL23->AddComponent<BoxCollisionComponent>(100, 20);
	platformL23->GetComponent<TransformComponent>()->SetPosition(302, 330, 0);
	platformL23->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL23);

	auto platformL33 = std::make_shared<dae::GameObject>();
	platformL33->AddComponent<BoxCollisionComponent>(100, 20);
	platformL33->GetComponent<TransformComponent>()->SetPosition(302, 266, 0);
	platformL33->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL33);

	auto platformL43 = std::make_shared<dae::GameObject>();
	platformL43->AddComponent<BoxCollisionComponent>(100, 20);
	platformL43->GetComponent<TransformComponent>()->SetPosition(302, 202, 0);
	platformL43->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL43);

	auto platformL53 = std::make_shared<dae::GameObject>();
	platformL53->AddComponent<BoxCollisionComponent>(100, 20);
	platformL53->GetComponent<TransformComponent>()->SetPosition(302, 170, 0);
	platformL53->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL53);

	auto platformL63 = std::make_shared<dae::GameObject>();
	platformL63->AddComponent<BoxCollisionComponent>(100, 20);
	platformL63->GetComponent<TransformComponent>()->SetPosition(302, 106, 0);
	platformL63->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL63);

#pragma endregion Platform row 7
#pragma region Platform row 8-9

	auto ladder15 = std::make_shared<dae::GameObject>();
	ladder15->AddComponent<BoxCollisionComponent>(20, 32);
	ladder15->GetComponent<TransformComponent>()->SetPosition(355, 234, 0);
	ladder15->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder15);

	auto ladder25 = std::make_shared<dae::GameObject>();
	ladder25->AddComponent<BoxCollisionComponent>(20, 32);
	ladder25->GetComponent<TransformComponent>()->SetPosition(355, 202, 0);
	ladder25->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder25);

	auto ladder35 = std::make_shared<dae::GameObject>();
	ladder35->AddComponent<BoxCollisionComponent>(20, 32);
	ladder35->GetComponent<TransformComponent>()->SetPosition(355, 170, 0);
	ladder35->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder35);

#pragma endregion Platform 8-9
#pragma region Platform row 8

	auto platformR15 = std::make_shared<dae::GameObject>();
	platformR15->AddComponent<BoxCollisionComponent>(100, 20);
	platformR15->GetComponent<TransformComponent>()->SetPosition(334, 394, 0);
	platformR15->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR15);

	auto platformR25 = std::make_shared<dae::GameObject>();
	platformR25->AddComponent<BoxCollisionComponent>(100, 20);
	platformR25->GetComponent<TransformComponent>()->SetPosition(334, 330, 0);
	platformR25->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR25);

	auto platformR35 = std::make_shared<dae::GameObject>();
	platformR35->AddComponent<BoxCollisionComponent>(100, 20);
	platformR35->GetComponent<TransformComponent>()->SetPosition(334, 266, 0);
	platformR35->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR35);

	auto platformR45 = std::make_shared<dae::GameObject>();
	platformR45->AddComponent<BoxCollisionComponent>(100, 20);
	platformR45->GetComponent<TransformComponent>()->SetPosition(334, 170, 0);
	platformR45->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR45);

	auto platformR55 = std::make_shared<dae::GameObject>();
	platformR55->AddComponent<BoxCollisionComponent>(100, 20);
	platformR55->GetComponent<TransformComponent>()->SetPosition(334, 106, 0);
	platformR55->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR55);

#pragma endregion Platform row 8
#pragma region Platform row 9

	auto platformR16 = std::make_shared<dae::GameObject>();
	platformR16->AddComponent<BoxCollisionComponent>(100, 20);
	platformR16->GetComponent<TransformComponent>()->SetPosition(366, 394, 0);
	platformR16->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR16);

	auto platformR26 = std::make_shared<dae::GameObject>();
	platformR26->AddComponent<BoxCollisionComponent>(100, 20);
	platformR26->GetComponent<TransformComponent>()->SetPosition(366, 330, 0);
	platformR26->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR26);

	auto platformR36 = std::make_shared<dae::GameObject>();
	platformR36->AddComponent<BoxCollisionComponent>(100, 20);
	platformR36->GetComponent<TransformComponent>()->SetPosition(366, 266, 0);
	platformR36->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR36);

	auto platformR46 = std::make_shared<dae::GameObject>();
	platformR46->AddComponent<BoxCollisionComponent>(100, 20);
	platformR46->GetComponent<TransformComponent>()->SetPosition(366, 170, 0);
	platformR46->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR46);

	auto platformR56 = std::make_shared<dae::GameObject>();
	platformR56->AddComponent<BoxCollisionComponent>(100, 20);
	platformR56->GetComponent<TransformComponent>()->SetPosition(366, 106, 0);
	platformR56->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR56);

#pragma endregion Platform row 9
#pragma region Platform row 10

	//ladders
	auto ladder16 = std::make_shared<dae::GameObject>();
	ladder16->AddComponent<BoxCollisionComponent>(20, 32);
	ladder16->GetComponent<TransformComponent>()->SetPosition(403, 362, 0);
	ladder16->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder16);

	auto ladder26 = std::make_shared<dae::GameObject>();
	ladder26->AddComponent<BoxCollisionComponent>(20, 32);
	ladder26->GetComponent<TransformComponent>()->SetPosition(403, 330, 0);
	ladder26->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder26);

	auto ladder36 = std::make_shared<dae::GameObject>();
	ladder36->AddComponent<BoxCollisionComponent>(20, 32);
	ladder36->GetComponent<TransformComponent>()->SetPosition(403, 298, 0);
	ladder36->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder36);

	auto ladder46 = std::make_shared<dae::GameObject>();
	ladder46->AddComponent<BoxCollisionComponent>(20, 32);
	ladder46->GetComponent<TransformComponent>()->SetPosition(403, 266, 0);
	ladder46->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder46);

	auto ladder56 = std::make_shared<dae::GameObject>();
	ladder56->AddComponent<BoxCollisionComponent>(20, 32);
	ladder56->GetComponent<TransformComponent>()->SetPosition(403, 234, 0);
	ladder56->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder56);

	auto ladder66 = std::make_shared<dae::GameObject>();
	ladder66->AddComponent<BoxCollisionComponent>(20, 32);
	ladder66->GetComponent<TransformComponent>()->SetPosition(403, 202, 0);
	ladder66->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder66);

	auto ladder76 = std::make_shared<dae::GameObject>();
	ladder76->AddComponent<BoxCollisionComponent>(20, 32);
	ladder76->GetComponent<TransformComponent>()->SetPosition(403, 170, 0);
	ladder76->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder76);

	auto ladder86 = std::make_shared<dae::GameObject>();
	ladder86->AddComponent<BoxCollisionComponent>(20, 32);
	ladder86->GetComponent<TransformComponent>()->SetPosition(403, 138, 0);
	ladder86->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder86);

	auto ladder96 = std::make_shared<dae::GameObject>();
	ladder96->AddComponent<BoxCollisionComponent>(20, 32);
	ladder96->GetComponent<TransformComponent>()->SetPosition(403, 106, 0);
	ladder96->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder96);

	//platform
	auto platformL14 = std::make_shared<dae::GameObject>();
	platformL14->AddComponent<BoxCollisionComponent>(100, 20);
	platformL14->GetComponent<TransformComponent>()->SetPosition(398, 394, 0);
	platformL14->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL14);

	auto platformL24 = std::make_shared<dae::GameObject>();
	platformL24->AddComponent<BoxCollisionComponent>(100, 20);
	platformL24->GetComponent<TransformComponent>()->SetPosition(398, 330, 0);
	platformL24->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL24);

	auto platformL34 = std::make_shared<dae::GameObject>();
	platformL34->AddComponent<BoxCollisionComponent>(100, 20);
	platformL34->GetComponent<TransformComponent>()->SetPosition(398, 298, 0);
	platformL34->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL34);

	auto platformL44 = std::make_shared<dae::GameObject>();
	platformL44->AddComponent<BoxCollisionComponent>(100, 20);
	platformL44->GetComponent<TransformComponent>()->SetPosition(398, 266, 0);
	platformL44->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL44);

	auto platformL54 = std::make_shared<dae::GameObject>();
	platformL54->AddComponent<BoxCollisionComponent>(100, 20);
	platformL54->GetComponent<TransformComponent>()->SetPosition(398, 234, 0);
	platformL54->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL54);

	auto platformL64 = std::make_shared<dae::GameObject>();
	platformL64->AddComponent<BoxCollisionComponent>(100, 20);
	platformL64->GetComponent<TransformComponent>()->SetPosition(398, 170, 0);
	platformL64->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL64);

	auto platformL74 = std::make_shared<dae::GameObject>();
	platformL74->AddComponent<BoxCollisionComponent>(100, 20);
	platformL74->GetComponent<TransformComponent>()->SetPosition(398, 106, 0);
	platformL74->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL74);

#pragma endregion Platform row 10
#pragma region platform row 11-12

	auto ladder17 = std::make_shared<dae::GameObject>();
	ladder17->AddComponent<BoxCollisionComponent>(20, 32);
	ladder17->GetComponent<TransformComponent>()->SetPosition(451, 362, 0);
	ladder17->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder17);

	auto ladder27 = std::make_shared<dae::GameObject>();
	ladder27->AddComponent<BoxCollisionComponent>(20, 32);
	ladder27->GetComponent<TransformComponent>()->SetPosition(451, 330, 0);
	ladder27->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder27);

	auto ladder37 = std::make_shared<dae::GameObject>();
	ladder37->AddComponent<BoxCollisionComponent>(20, 32);
	ladder37->GetComponent<TransformComponent>()->SetPosition(451, 298, 0);
	ladder37->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder37);

	auto ladder47 = std::make_shared<dae::GameObject>();
	ladder47->AddComponent<BoxCollisionComponent>(20, 32);
	ladder47->GetComponent<TransformComponent>()->SetPosition(451, 266, 0);
	ladder47->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder47);

	auto ladder57 = std::make_shared<dae::GameObject>();
	ladder57->AddComponent<BoxCollisionComponent>(20, 32);
	ladder57->GetComponent<TransformComponent>()->SetPosition(451, 234, 0);
	ladder57->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder57);

#pragma endregion platform row 11-12
#pragma region Platform row 11

	auto platformR17 = std::make_shared<dae::GameObject>();
	platformR17->AddComponent<BoxCollisionComponent>(100, 20);
	platformR17->GetComponent<TransformComponent>()->SetPosition(430, 394, 0);
	platformR17->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR17);

	auto platformR27 = std::make_shared<dae::GameObject>();
	platformR27->AddComponent<BoxCollisionComponent>(100, 20);
	platformR27->GetComponent<TransformComponent>()->SetPosition(430, 298, 0);
	platformR27->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR27);

	auto platformR37 = std::make_shared<dae::GameObject>();
	platformR37->AddComponent<BoxCollisionComponent>(100, 20);
	platformR37->GetComponent<TransformComponent>()->SetPosition(430, 234, 0);
	platformR37->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR37);

	auto platformR47 = std::make_shared<dae::GameObject>();
	platformR47->AddComponent<BoxCollisionComponent>(100, 20);
	platformR47->GetComponent<TransformComponent>()->SetPosition(430, 170, 0);
	platformR47->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR47);

	auto platformR57 = std::make_shared<dae::GameObject>();
	platformR57->AddComponent<BoxCollisionComponent>(100, 20);
	platformR57->GetComponent<TransformComponent>()->SetPosition(430, 106, 0);
	platformR57->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR57);

#pragma endregion Platform row 11
#pragma region Platform row 12

	auto platformR18 = std::make_shared<dae::GameObject>();
	platformR18->AddComponent<BoxCollisionComponent>(100, 20);
	platformR18->GetComponent<TransformComponent>()->SetPosition(462, 394, 0);
	platformR18->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR18);

	auto platformR28 = std::make_shared<dae::GameObject>();
	platformR28->AddComponent<BoxCollisionComponent>(100, 20);
	platformR28->GetComponent<TransformComponent>()->SetPosition(462, 298, 0);
	platformR28->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR28);

	auto platformR38 = std::make_shared<dae::GameObject>();
	platformR38->AddComponent<BoxCollisionComponent>(100, 20);
	platformR38->GetComponent<TransformComponent>()->SetPosition(462, 234, 0);
	platformR38->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR38);

	auto platformR48 = std::make_shared<dae::GameObject>();
	platformR48->AddComponent<BoxCollisionComponent>(100, 20);
	platformR48->GetComponent<TransformComponent>()->SetPosition(462, 170, 0);
	platformR48->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR48);

	auto platformR58 = std::make_shared<dae::GameObject>();
	platformR58->AddComponent<BoxCollisionComponent>(100, 20);
	platformR58->GetComponent<TransformComponent>()->SetPosition(462, 106, 0);
	platformR58->AddComponent<TextureRenderer>("platform2.png");
	scene1.Add(platformR58);

#pragma endregion Platform row 12
#pragma region Platform row 13

	//ladders
	auto ladder18 = std::make_shared<dae::GameObject>();
	ladder18->AddComponent<BoxCollisionComponent>(20, 32);
	ladder18->GetComponent<TransformComponent>()->SetPosition(499, 362, 0);
	ladder18->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder18);

	auto ladder28 = std::make_shared<dae::GameObject>();
	ladder28->AddComponent<BoxCollisionComponent>(20, 32);
	ladder28->GetComponent<TransformComponent>()->SetPosition(499, 330, 0);
	ladder28->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder28);

	auto ladder38 = std::make_shared<dae::GameObject>();
	ladder38->AddComponent<BoxCollisionComponent>(20, 32);
	ladder38->GetComponent<TransformComponent>()->SetPosition(499, 298, 0);
	ladder38->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder38);

	auto ladder48 = std::make_shared<dae::GameObject>();
	ladder48->AddComponent<BoxCollisionComponent>(20, 32);
	ladder48->GetComponent<TransformComponent>()->SetPosition(499, 202, 0);
	ladder48->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder48);

	auto ladder58 = std::make_shared<dae::GameObject>();
	ladder58->AddComponent<BoxCollisionComponent>(20, 32);
	ladder58->GetComponent<TransformComponent>()->SetPosition(499, 170, 0);
	ladder58->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder58);

	auto ladder68 = std::make_shared<dae::GameObject>();
	ladder68->AddComponent<BoxCollisionComponent>(20, 32);
	ladder68->GetComponent<TransformComponent>()->SetPosition(499, 138, 0);
	ladder68->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder68);

	auto ladder78 = std::make_shared<dae::GameObject>();
	ladder78->AddComponent<BoxCollisionComponent>(20, 32);
	ladder78->GetComponent<TransformComponent>()->SetPosition(499, 106, 0);
	ladder78->AddComponent<TextureRenderer>("Ladder.png");
	scene1.Add(ladder78);

	//platform
	auto platformL15 = std::make_shared<dae::GameObject>();
	platformL15->AddComponent<BoxCollisionComponent>(100, 20);
	platformL15->GetComponent<TransformComponent>()->SetPosition(494, 394, 0);
	platformL15->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL15);

	auto platformL25 = std::make_shared<dae::GameObject>();
	platformL25->AddComponent<BoxCollisionComponent>(100, 20);
	platformL25->GetComponent<TransformComponent>()->SetPosition(494, 298, 0);
	platformL25->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL25);

	auto platformL35 = std::make_shared<dae::GameObject>();
	platformL35->AddComponent<BoxCollisionComponent>(100, 20);
	platformL35->GetComponent<TransformComponent>()->SetPosition(494, 234, 0);
	platformL35->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL35);

	auto platformL45 = std::make_shared<dae::GameObject>();
	platformL45->AddComponent<BoxCollisionComponent>(100, 20);
	platformL45->GetComponent<TransformComponent>()->SetPosition(494, 170, 0);
	platformL45->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL45);

	auto platformL55 = std::make_shared<dae::GameObject>();
	platformL55->AddComponent<BoxCollisionComponent>(100, 20);
	platformL55->GetComponent<TransformComponent>()->SetPosition(494, 106, 0);
	platformL55->AddComponent<TextureRenderer>("platform1.png");
	scene1.Add(platformL55);

	

#pragma endregion Platform row 13

#pragma region 4plates

	auto plate1 = std::make_shared<dae::GameObject>();
	plate1->AddComponent<BoxCollisionComponent>(20, 20);
	plate1->GetComponent<TransformComponent>()->SetPosition(135, 450, 0);
	plate1->AddComponent<TextureRenderer>("pot.png");
	scene1.Add(plate1);

	auto plate2 = std::make_shared<dae::GameObject>();
	plate2->AddComponent<BoxCollisionComponent>(20, 20);
	plate2->GetComponent<TransformComponent>()->SetPosition(231, 450, 0);
	plate2->AddComponent<TextureRenderer>("pot.png");
	scene1.Add(plate2);

	auto plate3 = std::make_shared<dae::GameObject>();
	plate3->AddComponent<BoxCollisionComponent>(20, 20);
	plate3->GetComponent<TransformComponent>()->SetPosition(328, 450, 0);
	plate3->AddComponent<TextureRenderer>("pot.png");
	scene1.Add(plate3);

	auto plate4 = std::make_shared<dae::GameObject>();
	plate4->AddComponent<BoxCollisionComponent>(20, 20);
	plate4->GetComponent<TransformComponent>()->SetPosition(425, 450, 0);
	plate4->AddComponent<TextureRenderer>("pot.png");
	scene1.Add(plate4);

#pragma endregion 4plates

	// --- Bind All Commands ---
	bindCommands(character1, character2);

	
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}