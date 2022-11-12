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
  std::string contextTable;

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
            case UserInput::COMMANDS::COMMAND_REMOVE_TABLE:
              ui.SetState(UserInput::MENU_STATE::MENU_REMOVE_TABLE);
              break;
            case UserInput::COMMANDS::COMMAND_SWITCH_DB:
              ui.SetState(UserInput::MENU_STATE::MENU_OPEN_DATABASE);
              break;
            case UserInput::COMMANDS::COMMAND_QUIT:
              db.CloseCurrentDb();
              exit(0);
            case UserInput::COMMANDS::COMMAND_MODIFY:
              ui.SetState(UserInput::MENU_STATE::MENU_MODIFY_TABLE);
              break;
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
      case UserInput::MENU_STATE::MENU_REMOVE_TABLE:
        {
          std::string input = ui.MenuRemoveTable();

          ITableQueries* query = new SQLQuery();
          query->ComposeRemoveTableQuery(input);
          db.Interrogate(query);
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
      case UserInput::MENU_STATE::MENU_MODIFY_TABLE:
        {

          contextTable = ui.MenuModifyTable();

          //check if the table exists in the database
          ITableQueries* query = new SQLQuery();
          Table checkTable("_Tables");
          Field checkField("Name", "dummyValue");
          Condition checkCondition("Name", "=", contextTable);
          query->ComposeSelectQuery(checkTable, checkField, { checkCondition });
          std::vector<std::string> output = db.InterrogateWithReturn(query);

          if (output.empty())
          {
            std::cout << "There is not a table with this name in the database." << std::endl;
            ui.SetState(UserInput::MENU_STATE::MENU_MAIN);
            break;
          }

          switch (ui.GetCommand())
          {
            case UserInput::COMMANDS::COMMAND_MODIFY_ADD_ROW:
              ui.SetState(UserInput::MENU_STATE::MENU_MODIFY_TABLE_ADD_ROW);
              break;
            case UserInput::COMMANDS::COMMAND_MODIFY_REMOVE_ROW:
              ui.SetState(UserInput::MENU_STATE::MENU_MODIFY_TABLE_REMOVE_ROW);
              break;
            case UserInput::COMMANDS::COMMAND_MODIFY_UPDATE_ROW:
              ui.SetState(UserInput::MENU_STATE::MENU_MODIFY_TABLE_UPDATE_ROW);
              break;
            default:
              ui.SetState(UserInput::MENU_STATE::MENU_MAIN);
              break;
          }

          break;
        }
      case UserInput::MENU_STATE::MENU_MODIFY_TABLE_ADD_ROW:
        {
          std::string input = ui.MenuModifyAddRow();
          std::vector<std::string> values = Parser::ParseAddRow(input);
          
          //get the table columns
          ITableQueries* queryCheck = new SQLQuery();
          Table tableCheck("_Columns");
          Field fieldCheck("Name", "dummyValue");
          Condition conditionCheck("Table", "=", contextTable);
          queryCheck->ComposeSelectQuery(tableCheck, fieldCheck, { conditionCheck });
          std::vector<std::string> columnsNames = db.InterrogateWithReturn(queryCheck);

          std::vector<Field> fieldsToAdd;
          for (int i = 0; i < columnsNames.size(); i++)
          {
            fieldsToAdd.push_back({ Field(columnsNames.at(i), values.at(i)) });
          }

          ITableQueries* queryAdd = new SQLQuery();
          queryAdd->ComposeAddRowQuery(Table(contextTable), fieldsToAdd);
          db.Interrogate(queryAdd);

          ui.SetState(UserInput::MENU_STATE::MENU_MAIN);
          break;
        }
      case UserInput::MENU_STATE::MENU_MODIFY_TABLE_REMOVE_ROW:
        {
          std::string input = ui.MenuModifyRemoveRow();
          std::vector<Condition> conditions = Parser::ParseConditions(input);
          std::vector<std::string> logicOperators = Parser::ParseLogicOperator(input);

          ITableQueries* queryRemove = new SQLQuery();
          queryRemove->ComposeRemoveRowQuery(contextTable,conditions,logicOperators);
          db.Interrogate(queryRemove);

          ui.SetState(UserInput::MENU_STATE::MENU_MAIN);
          break;
        }
      case UserInput::MENU_STATE::MENU_MODIFY_TABLE_UPDATE_ROW:
        {
          std::vector<std::string> inputs = ui.MenuModifyUpdateRow();
          std::vector<Field> fields = Parser::ParseUpdateRow(inputs[0] + " " + inputs[1]);
          std::vector<Condition> conditions = Parser::ParseConditions(inputs[2]);
          std::vector<std::string> logicOperators = Parser::ParseLogicOperator(inputs[2]);

          ITableQueries* queryUpdate = new SQLQuery();
          queryUpdate->ComposeUpdateRowQuery(contextTable, fields, conditions, logicOperators);
          db.Interrogate(queryUpdate);

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