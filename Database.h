#pragma once
#include "pch.h"
#include "IQuery.h"
#include "Executor.h"
#include "ExecutorHandler.h"

class Database {

public:
  Database() = delete;
  Database(const std::string& aDatabasePath);
  ~Database();

  void Interrogate(IQuery* aQuery);

private:
  void OpenDatabase();

  PMSIHANDLE mHandle;
  std::string mDatabasePath;

};