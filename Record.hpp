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

#include <sqlite3.h>
#include <map>
#include <string>
#include <sstream>

using namespace std;

namespace sqlite3_cpp_helper_v2 {

  struct COLUMN_DESC {
    string type;
    int    max_length;
    bool   primary_key;
    bool   isNull;
    bool   not_null;
    string default_value;
    string value;
    bool   foreign_key;
    string reference_table;
    string reference_column;

    string operator()();
    string &operator = (int newValue);
    string &operator = (bool newValue);
    string &operator = (float newValue);
    string &operator = (string newValue);
    
    string Set(int newValue);
    string Set(bool newValue);
    string Set(float newValue);
    string Set(string newValue);
    string Set(const char *newValue);
  };

  typedef pair<string, COLUMN_DESC> COLUMN;
  typedef pair<int, string> COLUMNS_ORDER_ITEM;
  typedef map<string, COLUMN_DESC> COLUMNS_MAP;
  typedef map<int, string> COLUMNS_ORDER;
  
  class Record {
  private:
    COLUMNS_MAP columns;
    COLUMNS_ORDER order;

    string last_column;

    void create_column(string name, string type);
    void create_column(string name, string type, int max_length);

  public:
    Record();
    ~Record();

    Record *integer(string name);
    Record *text(string name);
    Record *text(string name, int max);
    Record *date(string name);
    Record *real(string name);
    Record *boolean(string name);
    
    Record *primary();
    Record *defaultValue(int value);
    Record *defaultValue(bool value);
    Record *defaultValue(float value);
    Record *defaultValue(string value);
    Record *defaultValue(const char *value);
    Record *foreign(string column);
    Record *references(string table, string column);

    //Record *NewRow();
    Record *Set(string column, int value);
    Record *Set(string column, bool value);
    Record *Set(string column, float value);
    Record *Set(string column, string value);
    Record *Set(string column, const char *value);
    
    string GenerateSql();

    string &operator () (string columnName);
    // char *operator [] (string columnName);
    // COLUMN_DESC &operator [] (string columnName);
    COLUMN_DESC &operator [] (string columnName);
  };
  
}
