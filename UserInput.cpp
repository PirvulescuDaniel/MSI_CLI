#include "UserInput.h"

UserInput::UserInput()
	:mState(UserInput::MENU_STATE::MENU_MAIN)
{
}

void UserInput::MenuMain()
{
	std::cout << "-------------MAIN MENU-------------" << std::endl;
	std::cout << "   1. create table" << std::endl;
	std::cout << "   2. modify table" << std::endl;
	std::cout << "   3. remove table" << std::endl << std::endl;
}

void UserInput::MenuAddTable()
{
	std::cout << "-------------ADD TABLE MENU-------------" << std::endl;
	std::cout << "Name of the table and columns numbers: " << std::endl;


}

UserInput::MENU_STATE UserInput::GetState()
{
	return mState;
}
