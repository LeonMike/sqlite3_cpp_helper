/*
  table.hpp is part of sqlite_cpp_helper.
  
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

#pragma once

#include <Record.hpp>

using namespace std;

namespace sqlite3_cpp_helper_v2 {

  class Table {
  private:
    sqlite3 *Db;
    COLUMNS_MAP columns;
    COLUMNS_ORDER order;

    string last_column;

    void create_column(string name, string type);
    void create_column(string name, string type, int max_length);

    string sqlSave();
  public:
    Table(sqlite3 *db);
    Table(Table &);
    ~Table();

    void   Create();

    string name;
    
    Table *integer(string name);
    Table *text(string name);
    Table *text(string name, int max);
    Table *date(string name);
    Table *real(string name);
    Table *boolean(string name);
    
    Table *primary();
    Table *defaultValue(int value);
    Table *defaultValue(bool value);
    Table *defaultValue(float value);
    Table *defaultValue(string value);
    Table *defaultValue(const char *value);
    Table *foreign(string column);
    Table *references(string table, string column);

    Table *NewRow();
    Table *Set(string column, int value);
    Table *Set(string column, bool value);
    Table *Set(string column, float value);
    Table *Set(string column, string value);
    Table *Set(string column, const char *value);
    Table *Save();
    
    string toSql();

    COLUMN_DESC &operator [](string name);
    string operator ()(string value);
  };
  
}
