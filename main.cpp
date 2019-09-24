#include <iostream>
#include <Database.hpp>
#include <tt.hpp>

using namespace std;
using namespace sqlite3_cpp_helper_v2;

void testing1() {
  // Record *r = new Record();
  // r
  //   ->integer("Id")
  //   ->text("text1")
  //   ->date("date1")
  //   ->real("real1");
  // (*r)["Id"] = "2";
  // (*r)["text1"] = "texto_2";
  // (*r)["date1"] = "01-01-2019";
  // (*r)["real1"] = 2.03f;
  // cout << r->GenerateSql() << endl;
  // cout << "\tId = " << (*r)("Id") << endl;
  // cout << "\ttext1 = " << (*r)("text1") << endl;
  // cout << "\tdate1 = " << (*r)("date1") << endl;
  // cout << "\treal1 = " << (*r)("real1") << endl;
  // delete r;
}

void testing2() {
  // Table *t = new Table("tab", (new Model())->integer("Id")->text("text")->date("date1")->real("real1"));
  // cout << t->GenerateSql() << endl;
  
  tt *t = new tt("tab.db");
  /*cout << (*t)["testing_table"].NewRow()
    ->Set("Id", 0)
    ->Set("name", "Ronny Barrera")->GenerateSql();
    (*t)["testing_table"].Save();*/
  //(*t)["testing_table"].Get();
  delete t;
}



int main() {
  //Database *db = new Database("t.db");
   /*db->New_Table("testing_table",
    		 (new Model())
    		 ->integer("id")
    		 ->text("name"));
		 (*db)["testing_table"].Create();*/
   
   // cout << (*db)["testing_table"].NewRow()
   //   ->Set("Id", 0)
   //  ->Set("name", "Ronny Barrera")->GenerateSql();
   // (*db)["testing_table"].Save();
   //delete db;
  testing2();
  return 0;
}
