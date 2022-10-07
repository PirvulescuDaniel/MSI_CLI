#pragma once

namespace Utility
{
  /*
    @return a string as std::wstring
  */
  std::wstring to_wstring(const std::string& aString)
  {
    return std::wstring(aString.begin(), aString.end());
  }

  /*
    Show a MessageBox with a specific message
  */
  void ShowMSB(const std::string& aMessage)
  {
    MessageBox(NULL, Utility::to_wstring(aMessage).c_str(), L"Error", NULL);
  }
}