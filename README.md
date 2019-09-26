# sqlite3_cpp_helper

This library allows a simple Database->Table->Model format to manage data

## Usage

TestingTable.hpp
```c++
#include <Table.hpp>

using namespace sqlite3_cpp_helper_v2;

class TestingTable: public Table {
public:
  TestingTable(sqlite3 *db, string tableName);
};
```

TestingDB.hpp
```c++
#include <Database.hpp>

using namespace sqlite3_cpp_helper_v2;

class TestingDB: public Database {
public:
  TestingDB(string db_filepath);
};
```

TestingTable.cpp
```c++
#include <TestingTable.hpp>

using namespace sqlite3_cpp_helper_v2;

TestingTable::TestingTable(string *db, string tableName): Table(db, tableName) {
  tableModel = (new Model())
    ->integer("Id")->primary()->autoincrement()
    ->text("name")
}
```

TestingDB.cpp
```c++
#include <TestingDB.hpp>

using namespace sqlite3_cpp_helper_v2;

TestingDB::TestingDB(string db_filepath): Database(db_filepath) {
  tables["testing_table"] = new TestingTable(Db, "testing_table");
  tables["testing_table"]->Create();
}
```

main.cpp
```c++
#include <TestingDB.hpp>

TestingDB *db;

using namespace std;
using namespace sqlite3_cpp_helper_v2;

int main(int argc, char **argv) {
  db = new TestingDB("database.db");
  (*db)["testing_table"].NewRow()
    ->Set("name", "user 1")->Save();
  (*db)["testing_table"].NewRow()
    ->Set("name", "user 2")->Save();
  vector<Model> result = (*db)["testing_table"].Get();
  for (int it = 0; it < result.size(); it++) {
    cout << result[it]("Id") << "\t" << result[it]("name") << endl;
  }
  delete db;
  return 0;
}
```
