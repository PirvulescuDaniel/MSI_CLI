#include "ExecutorHandler.h"

ExecutorHandler::ExecutorHandler(const Executor::EXECUTOR_ERROR& aError)
  :mError(aError)
{
  Handle();
}

/*
  Handle the error and stop the app
*/
void ExecutorHandler::Handle() const
{

  switch (mError.errorString)
  {
  case Executor::STRING_ERROR::SUCCESS:
    std::cout << "Command executed successfully!" << std::endl;
    break;
  case Executor::STRING_ERROR::VIEW_OPEN_ERROR:
    ShowError(L"VIEW_OPEN_ERROR", mError.errorCode);
    break;
  case Executor::STRING_ERROR::VIEW_EXECUTE_ERROR:
    ShowError(L"VIEW_EXECUTE_ERROR", mError.errorCode);
    break;
  }

  exit(0);
}

/*
  Show a message box that contains the error as string and the error code
*/
void ExecutorHandler::ShowError(const std::wstring& aErrorString, const UINT& aErrorCode) const
{
  std::wstring output = aErrorString + L": " + std::to_wstring(aErrorCode);
  MessageBox(NULL, output.c_str(), NULL, NULL);
}
