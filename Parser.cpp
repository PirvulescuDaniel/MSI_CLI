#include "Parser.h"
#include "Table.h"
#include "Field.h"

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
