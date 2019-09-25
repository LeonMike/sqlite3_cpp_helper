/*
  database.cpp is part of sqlite_cpp_helper.
  
  Foobar is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  Foobar is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <Database.hpp>

namespace sqlite3_cpp_helper_v2 {

  Database::Database(string filepath): db_filepath(filepath) {
    sqlite3_open(db_filepath.c_str(), &Db);
  }

  Database::~Database() {
    for (DB_TABLES_MAP::iterator it = tables.begin(); it != tables.end(); it++) {
      delete it->second;
    }
    sqlite3_close(Db);
    sqlite3_free(Db);
  }

  Table *Database::New_Table(string name) {
    tables[name] = new Table(Db, name);
  }
  
  Table *Database::New_Table(string name, Model *tableModel) {
    tables[name] = new Table(Db, name, tableModel);
    return tables[name];
  }

  Table & Database::operator [](string name) {
    return *tables[name];
  }

}
