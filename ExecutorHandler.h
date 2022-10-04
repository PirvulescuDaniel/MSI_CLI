#pragma once
#include "Executor.h"

class ExecutorHandler
{
public:
  ExecutorHandler(const Executor::EXECUTOR_ERROR& aError);

  void Handle() const;
  void ShowError(const std::wstring& aErrorString, const UINT& aErrorCode) const;

private:
  Executor::EXECUTOR_ERROR mError;

};