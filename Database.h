#pragma once
#include "pch.h"
#include "ITableQueries.h"
#include "Executor.h"
#include "ExecutorHandler.h"

class Database {

public:
  Database() = delete;
  Database(const std::string& aDatabasePath);

  void Interrogate(ITableQueries* aQuery);

private:
  void OpenDatabase();
  void Commit();

  PMSIHANDLE mHandle;
  std::string mDatabasePath;

};