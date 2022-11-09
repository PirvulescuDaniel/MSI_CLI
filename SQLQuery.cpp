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
  compose the query that select some fields from the table
*/
void SQLQuery::ComposeSelectQuery(
  const Table& aTable,
  const Field& aField,
  const std::vector<Condition>& aConditions)
{
  std::string queryTemp = "SELECT `" + aTable.GetName() + "`.`" + aField.GetName() + "` FROM `" + aTable.GetName() + '`';

  if (!aConditions.empty())
  {
    queryTemp += " WHERE ";
    for (const auto& condition : aConditions)
    {
      queryTemp += "`" + condition.GetLeftArgument() + "`" + condition.GetComparator() + "'" + condition.GetRightArgument() + "'";
      if (!(aConditions.back() == condition))
      {
        queryTemp += " AND ";
      }
    }
  }

  mQuery = queryTemp;
}

/*
  compose the query that add a row into a table
*/
void SQLQuery::ComposeAddRowQuery(const Table& aTable, const std::vector<Field> aFields)
{
  if (aFields.empty())
    return;

  std::string queryTemp = "INSERT INTO `" + aTable.GetName() + "` ";
  std::string composeColumnsPart;
  std::string composeValuesPart;
  unsigned int valuesNo = aFields.size();

  for (int i = 0; i < valuesNo - 1; i++)
  {
    composeColumnsPart += "`" + aTable.GetName() + "`.`" + aFields.at(i).GetName() + "` , ";
    composeValuesPart += "'" + aFields.at(i).GetValue() + "' ,";
  }
  composeColumnsPart += "`" + aTable.GetName() + "`.`" + aFields.at(valuesNo - 1).GetName() + "`";
  composeValuesPart += "'" + aFields.at(valuesNo - 1).GetValue() + "'";

  queryTemp += "( " + composeColumnsPart + " ) VALUES (" + composeValuesPart + " )";
  mQuery = queryTemp;
}

/*
  compose the query that remove a row into a table
*/
void SQLQuery::ComposeRemoveRowQuery(
  const Table& aTable,
  const std::vector<Condition> aConditions,
  const std::vector<std::string>& aLogicOperators)
{
  std::string queryTemp = "DELETE FROM `" + aTable.GetName() + "` WHERE ";

  if (aConditions.size() > 1)
    queryTemp += "(";

  for (size_t i = 0 ; i < aConditions.size(); i++)
  {
    queryTemp += "`" + aTable.GetName() + "`.`" +
                 aConditions[i].GetLeftArgument() + "`" +
                 aConditions[i].GetComparator() + "'" +
                 aConditions[i].GetRightArgument() + "'";

    if(i != aConditions.size() - 1)
      queryTemp += ' ' + aLogicOperators[i] + ' ';
  }

  if (aConditions.size() > 1)
    queryTemp += ")";

  mQuery = queryTemp;
}

/*
    @return the query as a std::string
*/
const std::string& SQLQuery::GetQuery() const
{
    return mQuery;
} 