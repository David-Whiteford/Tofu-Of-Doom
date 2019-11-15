#include "Controller.h"

CXBOXController::CXBOXController()
{
}

CXBOXController::~CXBOXController()
{
}

CXBOXController::CXBOXController(int playerNumber)
{
	// Set the Controller Number
	_controllerNum = playerNumber - 1;
}

XINPUT_STATE CXBOXController::GetState()
{
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	XInputGetState(_controllerNum, &_controllerState);

	return _controllerState;
}

bool CXBOXController::IsConnected()
{
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD Result = XInputGetState(_controllerNum, &_controllerState);

	if (Result == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CXBOXController::Vibrate(int leftVal, int rightVal)
{
	Player = new CXBOXController(m_playerID);
	// Create a Vibraton State
	XINPUT_VIBRATION Vibration;

	// Zeroise the Vibration
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	// Set the Vibration Values
	Vibration.wLeftMotorSpeed = leftVal;
	Vibration.wRightMotorSpeed = rightVal;

	// Vibrate the controller
	XInputSetState(Player->_controllerNum, &Vibration);
	delete(Player);
}

void CXBOXController::Update(float t_deltaTime)
{
	// Declare a temp Transform


	/*if (vibrationStarted + vibrationLength < t_deltaTime)
	{
		vibrate = false;
		Player1->Vibrate();
	////*/

	Player = new CXBOXController(m_playerID);

	if (Player->IsConnected())
	{
		if (Player->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			//	Player1->Vibrate(65535, 0);
		}

		if (Player->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			//Player1->Vibrate(0, 65535);
		}

		if (Player->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
		{
			//if (!vibrate)
			//{
			//	vibrate = true;
			//	Player1->Vibrate(65535, 65535);
			//	//vibrationStarted = t_deltaTime.asMilliseconds();
			//	//std::cout << vibrationStarted << std::endl;
			//}

		}

		if (Player->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			//	Player1->Vibrate();
		}

		if (Player->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
		{

		}

		if (Player->GetState().Gamepad.sThumbLY > 7849)
		{

		}
		else if (Player->GetState().Gamepad.sThumbLY < -7849)
		{
		}

		// Strafe
		if (Player->GetState().Gamepad.sThumbLX > 17849)
		{

		}
		else if (Player->GetState().Gamepad.sThumbLX < -17849)
		{
		}
		// End Strafe



		if (Player->GetState().Gamepad.sThumbRX < -7849)
		{
		}
		else if (Player->GetState().Gamepad.sThumbRX > 7849)
		{
			
		}
		if (Player->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			

		}
		else if (Player->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			

		}

		delete(Player);
	}
}

///<summary>
/// aButtonDown() checks if button was pressed down on current frame and 
/// not a continuation of being held down we can reuse aButton()
///</summmary>
bool CXBOXController::aButtonDown()
{
	if (aButton() && !aButtonPressed)
	{
		aButtonPressed = true;
		return true;
	}
	// holding A but button was already pressed down last frame
	else if (aButton() && aButtonPressed)
	{
		return false;
	}
	// is not pressing or holding A we reset the button going down to false
	else
	{
		aButtonPressed = false;
		return false;
	}
}

bool CXBOXController::yButtonDown()
{
	if (yButton() && !yButtonPressed)
	{
		aButtonPressed = true;
		return true;
	}
	// holding Y but button was already pressed down last frame
	else if (yButton() && yButtonPressed)
	{
		return false;
	}
	// is not pressing or holding Y we reset the button going down to false
	else
	{
		yButtonPressed = false;
		return false;
	}
}

bool CXBOXController::backButtonDown()
{
	if (backButton() && !backButtonPressed)
	{
		backButtonPressed = true;
		return true;
	}
	// holding Back but button was already pressed down last frame
	else if (backButton() && backButtonPressed)
	{
		return false;
	}
	// is not pressing or holding Back we reset the button going down to false
	else
	{
		backButtonPressed = false;
		return false;
	}
}

///<summary> 
/// aButton() checks for the continuation of a button being held down
///</summary>
bool CXBOXController::aButton()
{
	Player = new CXBOXController(m_playerID);

	if (Player->IsConnected())
	{
		if (Player->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			delete(Player); // remove instance from memeory
			return true;
		}
		// is not holding A 
		else
		{
			delete(Player);
			return false;

		}
	} // end is connected
	else
	{
		delete(Player);
		// No Controller found
		std::cout << "Error no controller found for Player 1" << std::endl;
		return false;
	}
}

///<summary> 
/// yButton() checks for the continuation of a button being held down
///</summary>
bool CXBOXController::yButton()
{
	Player = new CXBOXController(m_playerID);

	if (Player->IsConnected())
	{
		if (Player->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			delete(Player); // remove instance from memeory
			return true;
		}
		// is not holding Y
		else
		{
			delete(Player);
			return false;

		}
	} // end is connected
	else
	{
		delete(Player);
		// No Controller found
		std::cout << "Error no controller found for Player 1" << std::endl;
		return false;
	}
}

bool CXBOXController::backButton()
{
	Player = new CXBOXController(m_playerID);

	if (Player->IsConnected())
	{
		if (Player->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
		{
			delete(Player); // remove instance from memeory
			return true;
		}
		// is not holding Y
		else
		{
			delete(Player);
			return false;

		}
	} // end is connected
	else
	{
		delete(Player);
		// No Controller found
		std::cout << "Error no controller found for Player 1" << std::endl;
		return false;
	}
}

/// <summary> Detects a single up button press </summary>
bool CXBOXController::upButtonDown()
{
	if (upButton() && !upButtonPressed)
	{
		upButtonPressed = true;
		return true;
	}
	// holding up but button was already pressed down last frame
	else if (upButton() && upButtonPressed)
	{
		return false;
	}
	// is not pressing or holding up we reset the button going down to false
	else
	{
		upButtonPressed = false;
		return false;
	}
}

bool CXBOXController::upButton()
{
	Player = new CXBOXController(m_playerID);

	if (Player->IsConnected())
	{
		if (Player->GetState().Gamepad.sThumbLY > deadZone)
		{
			delete(Player);
			return true;
		}
		delete(Player);
		return false;
	}

	delete(Player);
	std::cout << "No Controller connected for port 1 player 1" << std::endl;
	return false;
}


/// <summary> Detects a single down button press </summary>
bool CXBOXController::downButtonDown()
{
	if (downButton() && !downButtonPressed)
	{
		downButtonPressed = true;
		return true;
	}
	// holding up but button was already pressed down last frame
	else if (downButton() && downButtonPressed)
	{
		return false;
	}
	// is not pressing or holding down we reset the button going down to false
	else
	{
		downButtonPressed = false;
		return false;
	}
}

bool CXBOXController::downButton()
{
	Player = new CXBOXController(m_playerID);

	if (Player->IsConnected())
	{
		if (Player->GetState().Gamepad.sThumbLY < -deadZone)
		{
			delete(Player);
			return true;
		}
		delete(Player);
		return false;
	}

	delete(Player);
	std::cout << "No Controller connected for port 1 player 1" << std::endl;
	return false;
}

bool CXBOXController::leftButton()
{
	Player = new CXBOXController(m_playerID);

	if (Player->IsConnected())
	{
		if (Player->GetState().Gamepad.sThumbLX < -deadZone)
		{
			delete(Player);
			return true;
		}
		delete(Player);
		return false;
	}

	delete(Player);
	std::cout << "No Controller connected for port 1 player 1" << std::endl;
	return false;
}

bool CXBOXController::rightButton()
{
	Player = new CXBOXController(m_playerID);

	if (Player->IsConnected())
	{
		if (Player->GetState().Gamepad.sThumbLX > deadZone)
		{
			delete(Player);
			return true;
		}
		delete(Player);
		return false;
	}

	delete(Player);
	std::cout << "No Controller connected for port 1 player 1" << std::endl;
	return false;
}



///<summary> Right Thumbstick Input for pressing left</summary>
bool CXBOXController::leftButtonRTS()
{
	Player = new CXBOXController(m_playerID);

	if (Player->IsConnected())
	{
		if (Player->GetState().Gamepad.sThumbRX < -deadZone)
		{
			delete(Player);
			return true;
		}
		delete(Player);
		return false;
	}

	delete(Player);
	std::cout << "No Controller connected for port 1 player 1" << std::endl;
	return false;
}



///<summary> Right Thumbstick Input for pressing right</summary>
bool CXBOXController::rightButtonRTS()
{
	Player = new CXBOXController(m_playerID);

	if (Player->IsConnected())
	{
		if (Player->GetState().Gamepad.sThumbRX > deadZone)
		{
			delete(Player);
			return true;
		}
		delete(Player);
		return false;
	}

	delete(Player);
	std::cout << "No Controller connected for port 1 player 1" << std::endl;
	return false;
}
