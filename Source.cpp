#include "pch.h"
#include "Database.h"
#include "Table.h"
#include "IQuery.h"
#include "SQLQuery.h"

int main(){

  const std::string path = "C:\\Users\\Daniel\\Desktop\\test.Msi";

  Database db(path);
  Table table("myTable");

  IQuery* query = new SQLQuery();
  query->ComposeAddTableQuery(table);

  db.Interrogate(query);

  delete query;

  //TODO
  // Add MsiCommitDatabase
  // and resolve invalid handle bug

  return 0;
}