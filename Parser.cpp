#include "pch.h"
#include "Utility.h"
#include "Parser.h"
#include "Table.h"
#include "Field.h"
#include "Condition.h"


Table Parser::ParseCreateTable(const std::string& aInput)
{
	std::vector<std::string> args;
	args = Utility::SplitByDelimiters(aInput, { " " });

	const std::string tableName = args[0];
	const std::vector<std::string> columnsNames(std::next(args.begin(), 2), args.end());

	std::vector<Field> fields;
	for (const auto& columnName : columnsNames)
	{
		fields.push_back(Field(columnName, "dummyValue"));
	}

	Row row(fields);
	const Table table(tableName, { row });
	return table;
}

std::vector<std::string> Parser::ParseAddRow(const std::string& aInput)
{
	std::vector<std::string> values = Utility::SplitByDelimiters(aInput, { " " });
	return values;
}

std::vector<Condition> Parser::ParseRemoveRow(const std::string& aInput)
{
	std::vector<Condition> conditions;

	std::vector<std::string> delimiters = { " AND ", " OR ", " and ", " or "};
	std::vector<std::string> condititionsStr = Utility::SplitByDelimiters(aInput, delimiters);

	for (const auto& conditionStr : condititionsStr)
	{
		std::vector<std::string> args = Utility::SplitByDelimiters(conditionStr, { "=" });
		conditions.push_back(Condition(args[0], "=", args[1]));
	}

	return conditions;
}

std::vector<std::string> Parser::ParseLogicOperator(const std::string& aInput)
{
	std::vector<std::string> output;

	std::vector<std::string> words = Utility::SplitByDelimiters(aInput, { " " });
	for (auto& word : words)
	{
		std::transform(word.begin(), word.end(), word.begin(), toupper);
		if (word == "AND" || word == "OR")
			output.push_back(word);
	}

	return output;
}