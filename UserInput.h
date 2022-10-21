#pragma once
#include "pch.h"

class UserInput
{
public:

	enum class MENU_STATE
	{
		MENU_MAIN,
		MENU_ADD_TABLE,
		MENU_OPEN_DATABASE,
		MENU_SWITCH_DATABASE
	};

	enum class COMMANDS
	{
		COMMAND_ADD_TABLE,
		COMMAND_SWITCH_DB,
		COMMAND_QUIT
	};

	UserInput();
	std::string GetDbPath();
	
	void MenuMain();
	std::string MenuAddTable();

	UserInput::MENU_STATE GetState() const;
	void SetState(const UserInput::MENU_STATE& aState);

	UserInput::COMMANDS GetCommand() const;

private:
	MENU_STATE mState;
	COMMANDS mCommand;
};