#pragma once
#include "pch.h"
#include "ITableQueries.h"
#include "Table.h"

class SQLQuery : public ITableQueries
{
public:
	void ComposeAddTableQuery(const Table& aTable);
	void ComposeRemoveTableQuery(const Table& aTable);
	void ComposeModifyTableQuery(const Table& aTable, const std::vector<Condition>& aConditions);

	void ComposeSelectQuery(
		const Table& aTable,
		const Field& aField,
		const std::vector<Condition>& aConditions);

	const std::string& GetQuery() const;

private:
	std::string mQuery;
};
