#pragma once
#include "Utility.h"

class Table;
class Field;

namespace Parser
{
	/*
		@return a Table, after string parsing
	*/
	Table ParseCreateTable(const std::string& aInput);

	/*
		Parse the AddRow Input
	*/
	std::vector<std::string> ParseAddRow(const std::string& aInput);

}