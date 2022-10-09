#include "Executor.h"

Executor::Executor(MSIHANDLE aHandle, ITableQueries* aQuery)
  :mDbHandle(aHandle)
  ,mViewHandle(NULL)
  ,mQuery(aQuery)
{
}

/*
  Close the handle to the view before destory executor obj
*/
Executor::~Executor()
{
  MsiCloseHandle(mViewHandle);
}

/*
  Execute a query
  @return an optinal value if an error eccurs
*/
std::optional<Executor::EXECUTOR_ERROR> Executor::Execute()
{
  std::wstring wquery(mQuery->GetQuery().begin(), mQuery->GetQuery().end());

  UINT viewResult = MsiDatabaseOpenView(mDbHandle, wquery.c_str(), &mViewHandle);
  if (viewResult != ERROR_SUCCESS)
  {
    return EXECUTOR_ERROR(Executor::STRING_ERROR::VIEW_OPEN_ERROR, viewResult);
  }

  UINT executeResult = MsiViewExecute(mViewHandle, 0);
  if (executeResult != ERROR_SUCCESS)
  {
    return EXECUTOR_ERROR(Executor::STRING_ERROR::VIEW_EXECUTE_ERROR, executeResult);
  }

  return std::nullopt;
}

/*
  Execute a query that can have results
*/
std::optional<std::vector<std::string>> Executor::ExecuteWithReturn()
{
  std::vector<std::string> records;

  std::optional<Executor::EXECUTOR_ERROR> error = Execute();
  if (error.has_value())
    return std::nullopt;

  MSIHANDLE recordHandle{};
  UINT fetchResult = MsiViewFetch(mViewHandle, &recordHandle);
  while (fetchResult != ERROR_NO_MORE_ITEMS)
  {
    DWORD size = MsiRecordDataSize(recordHandle, 1) + 1;
    char* content = new char[size + 1];

    MsiRecordGetStringA(recordHandle, 1, content, &size);
    records.push_back(content);

    delete[] content;
    fetchResult = MsiViewFetch(mViewHandle, &recordHandle);
  }

  return records;
}
