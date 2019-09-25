#include <tt.hpp>
#include <iostream>
#include <vector>

using namespace sqlite3_cpp_helper_v2;

ta::ta(sqlite3 *db): Table(db, "testing_table") {
  tableModel = (new sqlite3_cpp_helper_v2::Model())
    ->integer("id")->primary()->autoincrement()
    ->text("name");
}

// int ta::QueryCallback(int argc, char **argv, char **azColName) {
//   Model *m = new Model(*tableModel);
//   std::vector<Model *> result;
//   for (int i = 0; i < argc; i++) {
//     (*m).Set(azColName[i], argv[i] ? argv[i] : "NULL");
//   }
//   cout << "id = " << (*m)("id") << ";value = " << (*m)("name") << endl;
//   delete m;
//   return 0;
// }

tt::tt(string dbName): Database(dbName) {
  tables["testing_table"] = new ta(Db);
  tables["testing_table"]->Create();
}
