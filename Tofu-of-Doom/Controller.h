/// <summary>
/// Gotten from https://www.codeproject.com/articles/26949/xbox-360-controller-input-in-c-with-xinput
/// </summary>
#ifndef _XBOX_CONTROLLER_H_
#define _XBOX_CONTROLLER_H_

// No MFC
#define WIN32_LEAN_AND_MEAN

// We need the Windows Header and the XInput Header
#include <windows.h> 
#include "XInput.h"

// Now, the XInput Library
#pragma comment(lib, "XInput.lib")

#include <iostream>

// XBOX Controller Class Definition
class CXBOXController
{
private:
	XINPUT_STATE _controllerState;
	int _controllerNum;


	// Key presses hidden from player
	bool aButtonPressed = false;
	bool yButtonPressed = false;
	bool bButtonPressed = false;
	bool upButtonPressed = false;
	bool downButtonPressed = false;
	bool leftButtonPressed = false;
	bool rightButtonPressed = false;
	
	//===============EndKEyPresses Hidden from player

	float deadZone = 17000;

	int m_playerID = 1;

public:
	CXBOXController();
	~CXBOXController();
	CXBOXController(int playerNumber);
	XINPUT_STATE GetState();

	CXBOXController* Player;

	// Set and gets of player ID this will allow us to have other players if we so choose
	void setPlayerIndex(int t_playerNumber) { m_playerID = t_playerNumber; };
	int getPlayerIndex() { return m_playerID; };

	bool IsConnected();
	void Vibrate(int leftVal = 0, int rightVal = 0);
	void Update(float t_deltaTime);

	bool aButtonDown();
	bool aButton();

	bool bButtonDown();
	bool bButton();

	bool xButtonDown();
	bool xButton();

	bool yButtonDown();
	bool yButton();

	bool upButtonDown();
	bool upButton();

	bool downButtonDown();
	bool downButton();

	//bool leftButtonDown();
	bool leftButton();

	//bool rightButtonDown();
	bool rightButton();

	// Right Thumbstick input 
	bool rightButtonRTS();
	bool leftButtonRTS();


};

#endif