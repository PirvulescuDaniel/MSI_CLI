#pragma once
#include "pch.h"

namespace Utility
{
  /*
    @return a string as std::wstring
  */
	inline std::wstring to_wstring(const std::string& aString)
  {
    return std::wstring(aString.begin(), aString.end());
  }

  /*
    Show a MessageBox with a specific message
  */
	inline  void ShowMSB(const std::string& aMessage)
  {
    MessageBox(NULL, Utility::to_wstring(aMessage).c_str(), L"Error", NULL);
  }

	/*
		Split a string by multiple delimiters
	*/
	inline std::vector<std::string> SplitByDelimiters(const std::string& aString, std::vector<std::string> aDelimiters)
	{
		std::sort(aDelimiters.begin(), aDelimiters.end(),
			[](const std::string& first, const std::string& second) {
				return first.size() > second.size();
			}
		);

		std::vector<std::string> output;
		std::string stringCopy(aString);

		size_t index{};
		size_t delimSize{};

		while (true)
		{
			size_t indexMin = (std::numeric_limits<size_t>::max)();

			for (const auto& delimitator : aDelimiters)
			{
				index = stringCopy.find(delimitator);
				if (index != std::string::npos && index < indexMin)
				{
					indexMin = index;
					delimSize = delimitator.size();
				}
			}

			if (indexMin == (std::numeric_limits<size_t>::max)())
			{
				output.push_back(stringCopy);
				break;
			}

			output.push_back(stringCopy.substr(0, indexMin));
			stringCopy = stringCopy.substr(indexMin + delimSize, stringCopy.size());
		}

		auto last = std::remove_if(output.begin(), output.end(),
			[](const std::string& obj) {
				return obj.size() == 0;
			}
		);

		output = std::vector<std::string>(output.begin(), last);
		return output;
	}
}