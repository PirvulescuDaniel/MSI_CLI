#include "SQLQuery.h"
#include "Table.h"

/*
    compose the query that crates a table
*/
void SQLQuery::ComposeAddTableQuery(const Table& aTable)
{
    std::string queryTemp = "CREATE TABLE `" + aTable.GetName() + "`";

    if (!aTable.GetRows().empty())
    {
        queryTemp += " (";

        for (const auto& columnName : aTable.GetRows().at(0).GetFields())
        {
            queryTemp += "`" + columnName.GetName() + "` CHAR(255), ";
        }
        queryTemp.erase(queryTemp.size() - 2, std::string::npos);
        queryTemp += " PRIMARY KEY `" + aTable.GetRows().at(0).GetFields().at(0).GetName() + "`)";
    }

    mQuery = queryTemp;
} 

/*
    compose the query that remove a table
*/
void SQLQuery::ComposeRemoveTableQuery(const Table& aTable)
{
    mQuery = "DROP TABLE `" + aTable.GetName() + "`";
}

/*
    compose the query that modify a table by some conditions
*/
void SQLQuery::ComposeModifyTableQuery(const Table& aTable, const std::vector<Condition>& aConditions)
{
    //TODO
}

/*
    @return the query as a std::string
*/
const std::string& SQLQuery::GetQuery() const
{
    return mQuery;
}
