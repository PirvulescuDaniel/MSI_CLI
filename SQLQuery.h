#pragma once
#include "pch.h"
#include "IQuery.h"
#include "Table.h"

class SQLQuery : public IQuery
{
public:
	void ComposeAddTableQuery(const Table& aTable);
	void ComposeRemoveTableQuery(const Table& aTable);
	void ComposeModifyTableQuery(const Table& aTable, const std::vector<Condition>& aConditions);

	const std::string& GetQuery() const;

private:
	std::string mQuery;
};
