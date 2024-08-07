/*
  database.hpp is part of sqlite_cpp_helper.
  
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

#ifndef __SQLITE3_CPP_HELPER_DATABASE_HPP
#define __SQLITE3_CPP_HELPER_DATABASE_HPP

#include <sqlite3.h>
#include <string>
#include <map>
#include <Table.hpp>

using namespace std;

namespace sqlite3_helper {

  typedef map<string, Table *> DB_TABLES_MAP;
  
  class Database {
  private:
    string db_filepath;

  protected:
    sqlite3 *Db;
    
  public:
    Database(string filepath);
    void Dispose();

    DB_TABLES_MAP tables;
    
    Table *New_Table(string name);
    Table *New_Table(string name, Model *tableModel);

    Table &operator [](string name);
    
  };
  
}

#endif
