#pragma once
#include "Singleton.h"
#include <memory>
#include "Command.h"
#include <map>
#include <vector>
#include <SDL.h> // Include SDL.h to define SDL_ScanCode

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void BindCommand(SDL_Scancode key, std::unique_ptr <Command> command);
		bool IsPressed(SDL_Scancode key);
	private:
		std::map<SDL_Scancode, std::unique_ptr<Command>> m_Commands;
		void ExecuteCommand();
	};
}
