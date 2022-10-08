#include "pch.h"
#include "Database.h"
#include "Table.h"
#include "IQuery.h"
#include "SQLQuery.h"

int main(){

  const std::string path = "C:\\Users\\Dani\\Desktop\\test.Msi";

  Database db(path);

  std::vector<Field> fields = {
                              Field("col1","val1"),
                              Field("col2","val1"),
                              Field("col3","val1")
  };

  Row row(fields);
  std::vector<Row> rows;
  rows.push_back(row);

  Table table("myTable1", rows);

  IQuery* query = new SQLQuery();
  query->ComposeAddTableQuery(table);

  db.Interrogate(query);

  //TODO
  //check if already exists a table with that name in the database

  return 0;
}