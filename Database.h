#pragma once
#include "pch.h"
#include "ITableQueries.h"
#include "Executor.h"
#include "ExecutorHandler.h"

class Database {

public:
  Database() = delete;
  Database(const std::string& aDatabasePath);
  ~Database();

  void Interrogate(ITableQueries* aQuery);
  std::vector<std::string> InterrogateWithReturn(ITableQueries* aQuery);

  void CloseCurrentDb();
  void SwitchDatabase(const std::string& aPath);

private:
  void OpenDatabase();
  void Commit();

  MSIHANDLE mHandle;
  std::string mDatabasePath;

};