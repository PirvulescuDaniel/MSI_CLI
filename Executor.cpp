#include "Executor.h"

Executor::Executor(MSIHANDLE aHandle, ITableQueries* aQuery)
  :mHandle(aHandle)
  ,mQuery(aQuery)
{
}
/*
  Execute a query
  @return an optinal value if an error eccurs
*/
std::optional<Executor::EXECUTOR_ERROR> Executor::Execute()
{
  MSIHANDLE viewHandle;
  std::wstring wquery(mQuery->GetQuery().begin(), mQuery->GetQuery().end());

  UINT viewResult = MsiDatabaseOpenView(mHandle, wquery.c_str(), &viewHandle);
  if (viewResult != ERROR_SUCCESS)
  {
    return EXECUTOR_ERROR(Executor::STRING_ERROR::VIEW_OPEN_ERROR, viewResult);
  }

  UINT executeResult = MsiViewExecute(viewHandle, 0);
  if (executeResult != ERROR_SUCCESS)
  {
    return EXECUTOR_ERROR(Executor::STRING_ERROR::VIEW_EXECUTE_ERROR, executeResult);
  }

  MsiCloseHandle(viewHandle);
  return std::nullopt;
}
