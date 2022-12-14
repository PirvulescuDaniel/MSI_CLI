#include "Database.h"
#include "Utility.h"

Database::Database(const std::string& aDatabasePath)
  :mHandle(NULL)
  ,mDatabasePath(aDatabasePath)
{
  OpenDatabase();
}

/*
  Close the handle before destroy db object
*/
Database::~Database()
{
  UINT closeResult = MsiCloseHandle(mHandle);
  if (closeResult != ERROR_SUCCESS)
  {
    Utility::ShowMSB("Error at closing the database");
  }
}

/*
  Execute a query to databases
*/
void Database::Interrogate(ITableQueries* aQuery)
{
  Executor executor(mHandle,aQuery);
  std::optional<Executor::EXECUTOR_ERROR> error = executor.Execute();

  if (error.has_value())
  {
    ExecutorHandler executorHandler(error.value());
  }
  else
  {
    Commit();
    std::cout << "Command executed successfully!" << std::endl;
  }
}

/*
  Execute a query to databases that returns a vector with records
*/
std::vector<std::string> Database::InterrogateWithReturn(ITableQueries* aQuery)
{
  Executor executor(mHandle, aQuery);
  auto result = executor.ExecuteWithReturn();
  if (result.has_value())
  {
    return result.value();
  }

  return {};
}

/*
  Close the current database
*/
void Database::CloseCurrentDb()
{
  if (!mHandle)
    Utility::ShowMSB("There is no database in use.");

  UINT closeResult = MsiCloseHandle(mHandle);
  if (closeResult != ERROR_SUCCESS)
  {
    Utility::ShowMSB("Error at switching the database.");
  }
  system("cls");
  std::cout << "Database closed successfully" << std::endl;
}

/*
  Switch the database path
*/
void Database::SwitchDatabase(const std::string& aPath)
{
  mDatabasePath = aPath;
  OpenDatabase();
}

/*
  Open a database
*/
void Database::OpenDatabase()
{
  UINT openDbResult = MsiOpenDatabase(Utility::to_wstring(mDatabasePath).c_str(), MSIDBOPEN_TRANSACT, & mHandle);
  if (openDbResult != ERROR_SUCCESS)
  {
    Utility::ShowMSB("Error at opening database.\nError code: " + std::to_string(openDbResult));
    exit(0);
  }

  std::cout << "Database open successfully" << std::endl;
}

/*
  Commit the changes in the database
*/
void Database::Commit()
{
  UINT commitResult = MsiDatabaseCommit(mHandle);
  if (commitResult != ERROR_SUCCESS)
  {
    Utility::ShowMSB("Error at commiting changes on database");
    exit(0);
  }
}
