#include "UserInput.h"

UserInput::UserInput()
	:mState(UserInput::MENU_STATE::MENU_MAIN)
{
}

/*
	Show the main menu
*/
void UserInput::MenuMain()
{
	std::cout << "-------------MAIN MENU-------------" << std::endl;
	std::cout << "   1. create table" << std::endl;
	std::cout << "   2. modify table" << std::endl;
	std::cout << "   3. remove table" << std::endl << std::endl;

	std::string commandString;
	std::cin >> commandString;

	if (commandString == "create")
		mCommand = UserInput::COMMANDS::COMMAND_ADD_TABLE;
}

/*
	Get creating table input from the user
*/
std::string UserInput::MenuAddTable()
{
	std::cout << "-------------ADD TABLE MENU-------------" << std::endl;
	std::cout << "Name of the table and columns numbers: " << std::endl;

	std::string input;
	std::getline(std::cin, input);

	auto columnNumber = std::stoi( input.substr(input.find(" ") + 1, std::string::npos) );
	for (int index = 0; index < columnNumber; index++)
	{
		std::cout << "Column name: ";
		std::string column;
		std::cin >> column;
		input += " " + column;
	}

	return input;
}

/*
	Get the menu state
*/
UserInput::MENU_STATE UserInput::GetState() const
{
	return mState;
}

/*
	Set the menu state
*/
void UserInput::SetState(const UserInput::MENU_STATE& aState)
{
	mState = aState;
}

/*
	@return the mCommand
*/
UserInput::COMMANDS UserInput::GetCommand() const
{
	return mCommand;
}
