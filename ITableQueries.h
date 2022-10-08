#pragma once
#include "pch.h"
#include "Table.h"
#include "Condition.h"

class ITableQueries
{
public:
	virtual ~ITableQueries() = default;

	virtual void ComposeAddTableQuery(const Table& aTable) = 0;
	virtual void ComposeRemoveTableQuery(const Table& aTable) = 0;
	virtual void ComposeModifyTableQuery(const Table& aTable, const std::vector<Condition>& aConditions) = 0;

	virtual const std::string& GetQuery() const = 0;
};