#include "pch.h"
#include "Database.h"
#include "Table.h"
#include "ITableQueries.h"
#include "SQLQuery.h"
#include "UserInput.h"

int main(){

  UserInput ui;

  while (true)
  {
    switch (ui.GetState())
    {
      case UserInput::MENU_STATE::MENU_MAIN:
        {
          ui.MenuMain();
        
          switch (ui.GetCommand())
          {
            case UserInput::COMMANDS::COMMAND_ADD_TABLE:
              ui.SetState(UserInput::MENU_STATE::MENU_ADD_TABLE);
              break;
          }
          break;
        }
      case UserInput::MENU_STATE::MENU_ADD_TABLE:
        {
          std::string input = ui.MenuAddTable();
          ui.SetState(UserInput::MENU_STATE::MENU_MAIN);
          break;
        }
      default:
        {
          ui.SetState(UserInput::MENU_STATE::MENU_MAIN);
          break;
        }
    }

  }

  return 0;
}