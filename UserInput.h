#pragma once
#include "pch.h"

class UserInput
{
public:

	enum class MENU_STATE
	{
		MENU_MAIN,
		MENU_ADD_TABLE
	};

	UserInput();

	void MenuMain();
	void MenuAddTable();

	UserInput::MENU_STATE GetState();

private:
	MENU_STATE mState;
	std::string mCommand;
};