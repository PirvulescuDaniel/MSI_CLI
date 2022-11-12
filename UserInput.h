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
		MENU_SWITCH_DATABASE,
		MENU_MODIFY_TABLE,
		MENU_MODIFY_TABLE_ADD_ROW,
		MENU_MODIFY_TABLE_REMOVE_ROW,
		MENU_MODIFY_TABLE_UPDATE_ROW
	};

	enum class COMMANDS
	{
		COMMAND_ADD_TABLE,
		COMMAND_SWITCH_DB,
		COMMAND_QUIT,
		COMMAND_MODIFY,
		COMMAND_MODIFY_ADD_ROW,
		COMMAND_MODIFY_REMOVE_ROW,
		COMMAND_MODIFY_UPDATE_ROW
	};

	UserInput();
	std::string GetDbPath();
	
	void MenuMain();
	std::string MenuAddTable();
	std::string MenuModifyTable();
	std::string MenuModifyAddRow();
	std::string MenuModifyRemoveRow();
	std::vector<std::string> MenuModifyUpdateRow();

	UserInput::MENU_STATE GetState() const;
	void SetState(const UserInput::MENU_STATE& aState);

	UserInput::COMMANDS GetCommand() const;

private:
	MENU_STATE mState;
	COMMANDS mCommand;
};