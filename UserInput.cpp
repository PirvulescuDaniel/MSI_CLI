#include "UserInput.h"

UserInput::UserInput()
	:mState(UserInput::MENU_STATE::MENU_MAIN)
{
}


/*
	Interogate user for database path
*/
std::string UserInput::GetDbPath()
{
	std::string path;
	std::cout << "Database(MSI) path: ";
	std::getline(std::cin, path);
	return path;
}

/*
	Show the main menu
*/
void UserInput::MenuMain()
{
	std::cout << std::endl;
	std::cout << "-------------MAIN MENU-------------" << std::endl;
	std::cout << "   1. Create table" << std::endl;
	std::cout << "   2. Modify table" << std::endl;
	std::cout << "   3. Remove table" << std::endl;
	std::cout << "   4. Switch database" << std::endl;
	std::cout << "   5. Quit" << std::endl << std::endl;

	std::string commandString;
	std::getline(std::cin, commandString);

	commandString = commandString.substr(0, commandString.find(" "));

 	if (commandString == "create")
		mCommand = UserInput::COMMANDS::COMMAND_ADD_TABLE;

	if (commandString == "switch")
		mCommand = UserInput::COMMANDS::COMMAND_SWITCH_DB;

	if (commandString == "quit")
		mCommand = UserInput::COMMANDS::COMMAND_QUIT;
}

/*
	Get creating table input from the user
*/
std::string UserInput::MenuAddTable()
{
	std::cout << std::endl;
	std::cout << "-------------ADD TABLE MENU-------------" << std::endl;
	std::cout << "Name of the table and columns numbers: " << std::endl;

	std::string input;
	std::getline(std::cin, input);

	auto columnNumber = std::stoi( input.substr(input.find(" ") + 1, std::string::npos) );
	for (int index = 0; index < columnNumber; index++)
	{
		std::cout << "Column name: ";
		std::string column;
		std::getline(std::cin, column);
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
