#include "Parser.h"

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
