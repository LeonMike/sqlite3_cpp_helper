#include <iostream>
#include <Database.hpp>
#include <tt.hpp>

using namespace std;
using namespace sqlite3_cpp_helper_v2;

void testing2() {
  tt *t = new tt("tab.db");
  /*(*t)["testing_table"].NewRow()
    ->Set("name", "user 1")->Save();
  (*t)["testing_table"].NewRow()
    ->Set("name", "usuario __2__")->Save();
  (*t)["testing_table"].RetryLastSavingCommand();
  (*t)["testing_table"].NewRow()
  ->Set("name", "nuevo_usuario")->Save();*/
  vector<Model> result = (*t)["testing_table"].Get();
  for (int it = 0; it < result.size(); it++) {
    cout << result[it]("id") << "\t" << result[it]("name") << endl;
  }
  delete t;
}



int main() {
  testing2();
  return 0;
}
