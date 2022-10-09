#include "pch.h"
#include "Database.h"
#include "Table.h"
#include "ITableQueries.h"
#include "SQLQuery.h"

int main(){

  const std::string path = "C:\\Users\\Dani\\Desktop\\test.Msi";


  Table table("myTable");
  Field field("col1", "dummy");
  std::vector<Condition> conditions;

  ITableQueries* query = new SQLQuery;
  query->ComposeSelectQuery(table, field, conditions);

  std::cout << query->GetQuery();

  Database db(path);
  std::vector<std::string> results = db.InterrogateWithReturn(query);
  
  for (const auto& result : results)
  {
    std::cout << result << " ";
  }

  return 0;
}