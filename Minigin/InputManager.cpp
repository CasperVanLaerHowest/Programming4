#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>
#include "MoveCommand.h"

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
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	ExecuteCommand();

	return true;
}

void dae::InputManager::BindCommand(SDL_Scancode key, std::unique_ptr <Command> command)
{
	m_Commands[key] = std::move(command);
}

void dae::InputManager::ExecuteCommand()
{
	for (auto& command : m_Commands)
	{
		if (IsPressed(command.first)) {
			command.second->Execute();
		}
		//command.second->Execute();
	}
}

bool dae::InputManager::IsPressed(SDL_Scancode key)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[key]) {
		return true;
	}
	return false;
}