#include "pch.h"
#include "Database.h"
#include "Table.h"
#include "ITableQueries.h"
#include "SQLQuery.h"
#include "UserInput.h"
#include "Parser.h"

int main(){

  UserInput ui;
  std::string databasePath = ui.GetDbPath();

  Database db(databasePath);

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
            case UserInput::COMMANDS::COMMAND_SWITCH_DB:
              ui.SetState(UserInput::MENU_STATE::MENU_OPEN_DATABASE);
              break;
            case UserInput::COMMANDS::COMMAND_QUIT:
              db.CloseCurrentDb();
              exit(0);
          }
          break;
        }
      case UserInput::MENU_STATE::MENU_ADD_TABLE:
        {
          std::string input = ui.MenuAddTable();
          Table table = Parser::ParseCreateTable(input);

          //first check if the table already exists in the database

          ITableQueries* checkQuery = new SQLQuery();
          Table checkTable("_Tables");
          Field checkField("Name", "dummyValue");
          Condition checkCondition("Name", "=", table.GetName());
          checkQuery->ComposeSelectQuery(checkTable, checkField, { checkCondition });
          std::vector<std::string> tablesOutput = db.InterrogateWithReturn(checkQuery);

          if (!tablesOutput.empty())
          {
            std::cout << std::endl << "The table already exists in the database!" << std::endl;
          }
          else
          {
            ITableQueries* query = new SQLQuery();

            query->ComposeAddTableQuery(table);

            db.Interrogate(query);
          }
          ui.SetState(UserInput::MENU_STATE::MENU_MAIN);
          break;
        }
      case UserInput::MENU_STATE::MENU_OPEN_DATABASE:
        {
          db.CloseCurrentDb();
          databasePath = ui.GetDbPath();
          db.SwitchDatabase(databasePath);
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