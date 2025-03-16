#include "ControllerInput.h"
#include <cmath>


ControllerInput::ControllerInput()
	//: m_State{}
{
}

//bool ControllerInput::IsPressed(WORD button, SHORT* thumbX = nullptr, SHORT* thumbY = nullptr, BYTE* triggerR = nullptr, BYTE* triggerL = nullptr)
//{
//	ZeroMemory(&m_State, sizeof(XINPUT_STATE));
//	DWORD dwResult = XInputGetState(0, &m_State);
//	if (dwResult == ERROR_SUCCESS)
//	{
//		// Check digital buttons
//        if (button != 0 && (m_State.Gamepad.wButtons & button) != 0) {
//            return true;
//        }
//
//        // Check analog thumbsticks
//        if (thumbX != nullptr && std::abs(m_State.Gamepad.sThumbLX) > *thumbX) {
//            return true;
//        }
//        if (thumbY != nullptr && std::abs(m_State.Gamepad.sThumbLY) > *thumbY) {
//            return true;
//        }
//
//        // Check analog triggers
//        if (triggerL != nullptr && (m_State.Gamepad.bLeftTrigger > *triggerL)) {
//            return true;
//        }
//		if (triggerR != nullptr && (m_State.Gamepad.bRightTrigger > *triggerR)) {
//			return true;
//		}
//	}
//	return false;
//}

bool ControllerInput::IsPressed(Inputs input)
{
	XINPUT_STATE m_State;
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &m_State);
	if (dwResult == ERROR_SUCCESS)
	{
		switch (input)
		{
		case Inputs::A:
			return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0;
		case Inputs::B:
			return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0;
		case Inputs::X:
			return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0;
		case Inputs::Y:
			return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0;
		case Inputs::DPAD_UP:
			return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0;
		case Inputs::DPAD_DOWN:
			return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0;
		case Inputs::DPAD_LEFT:
			return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0;
		case Inputs::DPAD_RIGHT:
			return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0;
		case Inputs::START:
			return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0;
		case Inputs::BACK:
			return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0;
		case Inputs::LEFT_THUMB_UP:
			return m_State.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		case Inputs::LEFT_THUMB_DOWN:
			return m_State.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		case Inputs::LEFT_THUMB_LEFT:
			return m_State.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		case Inputs::LEFT_THUMB_RIGHT:
			return m_State.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		case Inputs::RIGHT_THUMB_UP:
			return m_State.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		case Inputs::RIGHT_THUMB_DOWN:
			return m_State.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		case Inputs::RIGHT_THUMB_LEFT:
			return m_State.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		case Inputs::RIGHT_THUMB_RIGHT:
			return m_State.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		case Inputs::LEFT_SHOULDER:
			return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0;
		case Inputs::RIGHT_SHOULDER:
			return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;
		}
	}
	return false;
}