#pragma once
#include "pch.h"
#include "ITableQueries.h"
#include "Table.h"

class SQLQuery : public ITableQueries
{
public:
	void ComposeAddTableQuery(const Table& aTable) override;
	void ComposeRemoveTableQuery(const Table& aTable) override;
	void ComposeModifyTableQuery(const Table& aTable, const std::vector<Condition>& aConditions) override;

	void ComposeSelectQuery(
		const Table& aTable,
		const Field& aField,
		const std::vector<Condition>& aConditions) override;

	const std::string& GetQuery() const;

	void ComposeAddRowQuery(const Table& aTable, const std::vector<Field> aFields) override;


private:
	std::string mQuery;
};
