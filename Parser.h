#pragma once

class Table;
class Field;
class Condition;

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

	/*
		Parse the RemoveRow Input
	*/
	std::vector<Condition> ParseRemoveRow(const std::string& aInput);

	/*
		Get the logic operators in the order that they apears in aInput
	*/
	std::vector<std::string> ParseLogicOperator(const std::string& aInput);
}