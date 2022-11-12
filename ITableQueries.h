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

	virtual void ComposeSelectQuery(const Table& aTable,
																	const Field& aField,
																	const std::vector<Condition>& aConditions) = 0;

	virtual void ComposeAddRowQuery(const Table& aTable, const std::vector<Field> aFields) = 0;
	virtual void ComposeRemoveRowQuery(const Table& aTable,
																		 const std::vector<Condition> aConditions,
																		 const std::vector<std::string>& aLogicOperators) = 0;
	virtual void ComposeUpdateRowQuery(const Table& aTable,
																		 const std::vector<Field> aFields,
																		 const std::vector<Condition> aConditions,
																		 const std::vector<std::string>& aLogicOperators) = 0;

	virtual const std::string& GetQuery() const = 0;
};