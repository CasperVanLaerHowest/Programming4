#pragma once
#include "Singleton.h"
#include <memory>
#include "Command.h"
#include <map>
#include <vector>
#include <SDL.h> // Include SDL.h to define SDL_ScanCode
#include "ControllerInput.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		bool ProcessInput();
		void BindCommand(SDL_Scancode key, std::unique_ptr <Command> command);
		void BindCommand(Inputs input, std::unique_ptr <Command> command);
		bool IsPressed(SDL_Scancode key);
		bool IsPressed(Inputs input);
	private:
		std::map<SDL_Scancode, std::unique_ptr<Command>> m_Commands;
		std::map<Inputs, std::unique_ptr<Command>> m_ControllerCommands;
		void ExecuteCommand();
		std::unique_ptr<ControllerInput> m_ControllerInput;
		std::map<Inputs, bool> m_ControllerInputState;
		std::map<SDL_Scancode, bool> m_KeyboardInputState;

		void UpdateKeyboardInputState();
		void UpdateControllerInputState();

	};
}
