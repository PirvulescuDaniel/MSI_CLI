#include "pch.h"
#include "Database.h"
#include "Table.h"
#include "ITableQueries.h"
#include "SQLQuery.h"

int main(){

  const std::string path = "C:\\Users\\Dani\\Desktop\\test.Msi";

  SQLQuery query;

  Table table("myTable");
  Field field("col1", "val1");
  Condition("col1", "=", "val1");

  std::vector<Condition> myVec = {
    Condition("col1", "=", "val1"),
    Condition("col2", "<", "val2"),
    Condition("col3", ">", "val3"),
    Condition("col4", "<>", "val4")
  };

  query.ComposeSelectQuery(table, field, myVec);

  std::cout << query.GetQuery();

  //TODO
  //check if already exists a table with that name in the database

  return 0;
}