#include "Table.h"
#include "Row.h"

/*
	create an empty table with name "aName"
*/
Table::Table(const std::string& aName)
	:mName(aName)
{

}

/*
	create a table named "aName" with rows "aRows"
*/
Table::Table(const std::string& aName, const std::vector<Row>& aRows)
	: mName(aName)
	,mRows(aRows)
{
}

/*
	@return the name of the table as a string
*/
const std::string& Table::GetName() const
{
	return mName;
}

/*
	@return all rows of the table as vector<Row>
*/
const std::vector<Row>& Table::GetRows() const
{
	return mRows;
}

/*
	add a row at the end of the table 
*/
void Table::AddRow(const Row& aRow)
{
	mRows.push_back(aRow);
}

/*
	remove a row by index
*/
void Table::RemoveRow(const size_t& aIndex)
{
	auto rowIterator = mRows.begin();
	std::advance(rowIterator, aIndex);
	mRows.erase(rowIterator);
}
