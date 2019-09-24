#include <tt.hpp>

ta::ta(sqlite3 *db): Table(db, "testing_table") {
  tableModel = (new sqlite3_cpp_helper_v2::Model())
    ->integer("id")->primary()
    ->text("name");
}

tt::tt(string dbName): Database(dbName) {
  tables["testing_table"] = new ta(Db);
  tables["testing_table"]->Create();
}
