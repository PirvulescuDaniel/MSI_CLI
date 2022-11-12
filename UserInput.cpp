#include "UserInput.h"
#include "Utility.h"

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

	if (commandString == "modify")
		mCommand = UserInput::COMMANDS::COMMAND_MODIFY;
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
	Show modify table menu and return the input
*/
std::string UserInput::MenuModifyTable()
{
	std::cout << std::endl;
	std::cout << "-------------MODIFY TABLE MENU-------------" << std::endl;
	std::cout << "   1.\"table_name\" add row " << std::endl;
	std::cout << "   2.\"table_name\" remove row" << std::endl;
	std::cout << "   3.\"table_name\" update row" << std::endl << std::endl;

	std::string input;
	std::getline(std::cin, input);

	std::vector<std::string> args = Utility::SplitByDelimiters(input, { " " });
	std::string tableName = args[0];
	std::string command = args[1];

	if (command == "add")
		mCommand = UserInput::COMMANDS::COMMAND_MODIFY_ADD_ROW;

	if (command == "remove")
		mCommand = UserInput::COMMANDS::COMMAND_MODIFY_REMOVE_ROW;

	if (command == "update")
		mCommand = UserInput::COMMANDS::COMMAND_MODIFY_UPDATE_ROW;

	return tableName;
}

/*
	Show remove row menu and return the input
*/
std::string UserInput::MenuModifyRemoveRow()
{
	std::cout << "Condition list(e.g: col1=val1 AND col2=val2 OR col3=val3):" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	return input;
}

/*
	Show update row menu and return the input
*/
std::vector<std::string> UserInput::MenuModifyUpdateRow()
{
	std::vector<std::string> outputs = { "","","" };

	std::cout << "The column(s) you want to modify: " << std::endl;
	std::getline(std::cin, outputs[0]);
	std::cout << std::endl;

	std::cout << "The value(s) for each column: " << std::endl;
	std::getline(std::cin, outputs[1]);
	std::cout << std::endl;

	std::cout << "Conditions: " << std::endl;
	std::getline(std::cin, outputs[2]);
	std::cout << std::endl;
	
	return outputs;
}

/*
	Show add row menu and return the input
*/
std::string UserInput::MenuModifyAddRow()
{
	std::cout << "Write the list of values." << std::endl;

	std::string input;
	std::getline(std::cin, input);
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
