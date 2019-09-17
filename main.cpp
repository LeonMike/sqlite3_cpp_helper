#include <iostream>
#include <Database.hpp>

using namespace std;
using namespace sqlite3_cpp_helper_v2;

int main() {
  // Database *db = new Database("t.db");
  // db->New_Table("testing_table")
  //   ->integer("id")
  //   ->text("name")
  //   ->Create();
  // delete db;
  Record *r = new Record();
  r
    ->integer("Id")
    ->text("text1")
    ->date("date1")
    ->real("real1");
  r->Set("Id", 1);
  r->Set("text1", "texto_1");
  r->Set("date1", "01-01-2019");
  r->Set("real1", 2.03f);
  cout << r->GenerationSql() << endl;
  cout << "\tId = " << (*r)["Id"] << endl;
  cout << "\ttext1 = " << (*r)["text1"] << endl;
  cout << "\tdate1 = " << (*r)["date1"] << endl;
  cout << "\treal1 = " << (*r)["real1"]<< endl;
  delete r;
  return 0;
}
