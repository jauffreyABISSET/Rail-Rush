#pragma once
#include "Character.h"

class Controller
{
	Character* mPlayer;

public:
	Controller(Character* player) { mPlayer = player; }

	void HandleMovement(float deltaTime, float spacingZ, float groundY);
	void MenuMovement(float deltaTime, float spacingZ, float groundY);
	void DefeatMovement(float deltaTime, float spacingZ, float groundY);
};