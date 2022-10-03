#pragma once
#include "pch.h"
#include "Row.h"

class Table
{
public:
	Table() = default;
	Table(const std::string& aName);
	Table(const std::string& aName ,const std::vector<Row>& aRows);

	const std::string& GetName() const;
	const std::vector<Row>& GetRows() const;

	void AddRow(const Row& aRow);
	void RemoveRow(const size_t& aIndex);

private:
	std::string mName;
	std::vector<Row> mRows;
};