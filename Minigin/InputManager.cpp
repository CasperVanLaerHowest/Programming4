#include <SDL.h>
#include "InputManager.h"
#include "MoveCommand.h"
#include "ControllerInput.h"

dae::InputManager::InputManager()
{
	m_ControllerInput = std::make_unique<ControllerInput>();
}

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	ExecuteCommand();

	return true;
}

void dae::InputManager::BindCommand(SDL_Scancode key, std::unique_ptr <Command> command)
{
	m_Commands[key] = std::move(command);
	m_KeyboardInputState[key] = false;
}

void dae::InputManager::BindCommand(Inputs input, std::unique_ptr <Command> command)
{
	m_ControllerCommands[input] = std::move(command);
	m_ControllerInputState[input] = false;
}

void dae::InputManager::ExecuteCommand()
{
	for (auto& command : m_Commands)
	{
		if (IsPressed(command.first)) {
			command.second->Execute(m_KeyboardInputState[command.first]);
            
		}
	}

	for (auto& command : m_ControllerCommands)
	{
		if (IsPressed(command.first)) {
			command.second->Execute(true);
		}
	}

	UpdateKeyboardInputState();
	UpdateControllerInputState();
}

bool dae::InputManager::IsPressed(SDL_Scancode key)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[key]) {
		return true;
	}
	return false;
}

bool dae::InputManager::IsPressed(Inputs input)
{
	if (m_ControllerInput->IsPressed(input)) {
		return true;
	}
	return false;
}

void dae::InputManager::UpdateKeyboardInputState()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	for (auto& key : m_KeyboardInputState)
	{
		key.second = state[key.first];
	}
}

void dae::InputManager::UpdateControllerInputState()
{
	for (auto& input : m_ControllerInputState)
	{
		input.second = m_ControllerInput->IsPressed(input.first);
	}
}