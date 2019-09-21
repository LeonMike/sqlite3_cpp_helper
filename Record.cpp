/*
  table.cpp is part of sqlite_cpp_helper.
  
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

#include <Record.hpp>
#include <sstream>
#include <iostream>

using namespace std;

namespace sqlite3_cpp_helper_v2 {

  string COLUMN_DESC::operator ()() {
    return value;
  }

  string &COLUMN_DESC::operator = (int newValue) {
    isNull = true;
    if (&newValue != NULL) {
      stringstream ss;
      ss << newValue;
      value = ss.str();
     isNull = false;
    }
    return value;
  }

  string &COLUMN_DESC::operator = (bool newValue) {
    isNull = true;
    if (&newValue != NULL) {
      stringstream ss;
      ss << newValue;
      value = ss.str();
     isNull = false;
    }
    return value;
  }

  string &COLUMN_DESC::operator = (float newValue) {
    isNull = true;
    if (&newValue != NULL) {
      stringstream ss;
      ss << newValue;
      value = ss.str();
      isNull = false;
    }
    return value;
  }

  string &COLUMN_DESC::operator = (string newValue) {
    isNull = false;
    value = newValue;
    return value;
  }
  
  string COLUMN_DESC::Set(int newValue) {
    isNull = true;
    if (&newValue != NULL) {
      stringstream ss;
      ss << newValue;
      value = ss.str();
      isNull = false;
    }
    return value;
  }

  string COLUMN_DESC::Set(bool newValue) {
    isNull = true;
    if (&newValue != NULL) {
      stringstream ss;
      ss << newValue;
      value = ss.str();
     isNull = false;
    }
    return value;
  }
  
  string COLUMN_DESC::Set(float newValue) {
    isNull = true;
    if (&newValue != NULL) {
      stringstream ss;
      ss << newValue;
      value = ss.str();
      isNull = false;
    }
    return value;
  }

  string COLUMN_DESC::Set(string newValue) {
    isNull = false;
    value = newValue;
    return value;
  }

  string COLUMN_DESC::Set(const char *newValue) {
    isNull = true;
    if (newValue != NULL) {
      stringstream ss(newValue);
      value = ss.str();
      isNull = false;
    }
    return value;
  }
  
  Record::Record() {}
  //Record::Record(Table &base): {}
  Record::~Record() { columns.clear(); }

  void Record::create_column(string name, string type) {
    COLUMN_DESC desc;
    desc.type = type;
    desc.max_length = 0;
    desc.primary_key = false;
    desc.isNull = true;
    desc.not_null = false;
    desc.default_value = "NULL";
    desc.value = "";
    desc.foreign_key = false;
    desc.reference_table = "";
    desc.reference_column = "";
    columns.insert(COLUMN(name, desc));
    order.insert(COLUMNS_ORDER_ITEM(columns.size() - 1, name));
    last_column = name;
  }

  void Record::create_column(string name, string type, int max_length) {
    COLUMN_DESC desc;
    desc.type = type;
    desc.max_length = max_length;
    desc.primary_key = false;
    desc.isNull = true;
    desc.not_null = false;
    desc.default_value = "NULL";
    desc.value = "";
    desc.foreign_key = false;
    desc.reference_table = "";
    desc.reference_column = "";
    columns.insert(COLUMN(name, desc));
    order.insert(COLUMNS_ORDER_ITEM(columns.size() - 1, name));
    last_column = name;
  }
  
  Record *Record::integer(string name) { create_column(name, "INT"); return this; }
  Record *Record::text(string name) { create_column(name, "TEXT"); return this; }
  Record *Record::text(string name, int max_length) { create_column(name, "VARCHAR", max_length); return this; }
  Record *Record::date(string name) { create_column(name, "DATE"); return this; }
  Record *Record::real(string name) { create_column(name, "REAL"); return this; }
  Record *Record::boolean(string name) { create_column(name, "BOOLEAN"); return this; }
  
  Record *Record::primary() { columns[last_column].primary_key = true; return this; }
  Record *Record::defaultValue(int value) { stringstream ss; ss << value; columns[last_column].default_value = ss.str(); return this; }
  Record *Record::defaultValue(bool value) { stringstream ss; ss << (value ? 1 : 0); columns[last_column].default_value = ss.str(); return this; }
  Record *Record::defaultValue(float value) { stringstream ss; ss << value; columns[last_column].default_value = ss.str(); return this; }
  Record *Record::defaultValue(string value) { columns[last_column].default_value = "'" + value + "'"; return this; }
  Record *Record::defaultValue(const char *value) { stringstream ss(value); columns[last_column].default_value = "'" + ss.str() + "'"; return this; }
  Record *Record::foreign(string column) { columns[column].foreign_key = true; last_column = column; return this; }
  Record *Record::references(string table, string column) { columns[last_column].reference_table = table; columns[last_column].reference_column = column; return this; }

  Record *Record::Set(string columnName, int value) {
    columns[columnName].isNull = true;
    if (&value != NULL) {
      stringstream ss("");
      ss << value;
      //columns[columnName].value = ss.str();
      columns[columnName] = ss.str();
      columns[columnName].isNull = false;
    }
    return this;
  }

  Record *Record::Set(string columnName, bool value) {
    columns[columnName].isNull = true;
    if (&value != NULL) {
      stringstream ss("");
      ss << value;
      //columns[columnName].value = ss.str();
      columns[columnName] = ss.str();
      columns[columnName].isNull = false;
    }
    return this;
  }
  
  Record *Record::Set(string columnName, float value) {
    columns[columnName].isNull = true;
    if (&value != NULL) {
      stringstream ss("");
      ss << value;
      //columns[columnName].value = ss.str();
      columns[columnName] = ss.str();
      columns[columnName].isNull = false;
    }
    return this;
  }

  Record *Record::Set(string columnName, string value) {
    cout << "storing: " << value << endl;
    //columns[columnName].value = value;
    columns[columnName] = value;
    columns[columnName].isNull = false;
    return this;
  }

  Record *Record::Set(string columnName, const char *newValue) {
    columns[columnName].isNull = true;
    if (newValue != NULL) {
      stringstream ss(newValue);
      columns[columnName] = ss.str();
      columns[columnName].isNull = false;
    }
    return this;
  }
  
  string Record::GenerateSql() {
    string result = "";
    if (columns.size() > 0) {
      stringstream columnsStr("");
      string foreignsStr = "";
      for (COLUMNS_ORDER_ITEM item : order) {
	if (columnsStr.str() != "") {
	  columnsStr << ", ";
	}
	if (columns[item.second].foreign_key) {
	  foreignsStr += ", " \
	    "FOREIGN KEY(" + item.second + ") "				\
	    "REFERENCES " + columns[item.second].reference_table + "(" + columns[item.second].reference_column + ")";
	}
	columnsStr <<
	  item.second << " " <<
	  columns[item.second].type;
	if (columns[item.second].max_length != 0) {
	  columnsStr << "(" << columns[item.second].max_length << ")";
	}
	columnsStr <<
	  (columns[item.second].primary_key ? " PRIMARY KEY" : "") <<
	  (columns[item.second].default_value != "" ? " DEFAULT " + columns[item.second].default_value : "") <<
	  (columns[item.second].not_null ? " NOT NULL" : "");
      }
      result += " (" + columnsStr.str() + foreignsStr + ")";
    }
    return result;
  }

  string &Record::operator ()(string columnName) {
    return columns[columnName.c_str()].value;
  }

  // COLUMN_DESC &Record::operator [](string columnName) {
  //   return columns[columnName.c_str()];
  // }
  
  // char *Record::operator [](string columnName) {
  //   return columns[columnName.c_str()].value.c_str();
  // }

  COLUMN_DESC &Record::operator [](string columnName) {
    return columns[columnName.c_str()];
  }

}
