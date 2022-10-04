#pragma once
#include "pch.h"
#include "IQuery.h"
#include "SQLQuery.h"

class Executor
{
public:

  enum class STRING_ERROR { SUCCESS, VIEW_OPEN_ERROR, VIEW_EXECUTE_ERROR };

  struct EXECUTOR_ERROR {
    EXECUTOR_ERROR(STRING_ERROR aErrorString, UINT aErrorCode) : errorString(aErrorString), errorCode(aErrorCode) {}
    STRING_ERROR errorString;
    UINT errorCode;
  };

  Executor() = delete;
  Executor(PMSIHANDLE aHandle, IQuery* aQuery);

  std::optional<EXECUTOR_ERROR> Execute();

private:
  PMSIHANDLE mHandle;
  std::shared_ptr<IQuery> mQuery;
};