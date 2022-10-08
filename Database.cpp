#include "Database.h"
#include "Utility.h"

Database::Database(const std::string& aDatabasePath)
  :mHandle(NULL)
  ,mDatabasePath(aDatabasePath)
{
  OpenDatabase();
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
