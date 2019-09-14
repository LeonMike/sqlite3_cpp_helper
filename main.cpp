#include <iostream>
#include <Database.hpp>

using namespace sqlite3_cpp_helper_v2;

int main() {
  Database *db = new Database("t.db");
  db->New_Table("testing_table")
    ->integer("id")
    ->text("name")
    ->Create();
  delete db;
  return 0;
}
