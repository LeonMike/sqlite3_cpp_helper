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

#include <Model.hpp>
#include <sstream>
#include <iostream>
#include <assert.h>

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
  
  Model::Model() {}
  //Model::Model(Table &base): {}
  Model::~Model() { columns.clear(); }

  int Model::ColumnsCount() { return columns.size(); }
  
  void Model::create_column(string name, string type) {
    isInserting = false;
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

  void Model::create_column(string name, string type, int max_length) {
    isInserting = false;
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

  Model *Model::New() {
    isInserting = true;
    assert(columns.size() > 0);
    cout << "\033[1;33mCleaning model...\033[0;0m" << endl;
    for (COLUMN col : columns) {
      col.second.value = "";
      col.second.isNull = true;
    }
    return this;
  }
  
  Model *Model::integer(string name) { create_column(name, "INTEGER"); return this; }
  Model *Model::text(string name) { create_column(name, "TEXT"); return this; }
  Model *Model::text(string name, int max_length) { create_column(name, "VARCHAR", max_length); return this; }
  Model *Model::date(string name) { create_column(name, "DATE"); return this; }
  Model *Model::real(string name) { create_column(name, "REAL"); return this; }
  Model *Model::boolean(string name) { create_column(name, "BOOLEAN"); return this; }
  
  Model *Model::primary() { isInserting = false; columns[last_column].primary_key = true; return this; }
  Model *Model::autoincrement() { isInserting = false; columns[last_column].auto_increment = true; columns[last_column].default_value = ""; return this; }
  Model *Model::defaultValue(int value) { stringstream ss; isInserting = false; ss << value; columns[last_column].default_value = ss.str(); return this; }
  Model *Model::defaultValue(bool value) { stringstream ss; isInserting = false; ss << (value ? 1 : 0); columns[last_column].default_value = ss.str(); return this; }
  Model *Model::defaultValue(float value) { stringstream ss; isInserting = false; ss << value; columns[last_column].default_value = ss.str(); return this; }
  Model *Model::defaultValue(string value) { isInserting = false; columns[last_column].default_value = "'" + value + "'"; return this; }
  Model *Model::defaultValue(const char *value) { stringstream ss(value); isInserting = false; columns[last_column].default_value = "'" + ss.str() + "'"; return this; }
  Model *Model::foreign(string column) { isInserting = false; columns[column].foreign_key = true; last_column = column; return this; }
  Model *Model::references(string table, string column) { isInserting = false; columns[last_column].reference_table = table; columns[last_column].reference_column = column; return this; }

  Model *Model::Set(string columnName, int value) {
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

  Model *Model::Set(string columnName, bool value) {
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
  
  Model *Model::Set(string columnName, float value) {
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

  Model *Model::Set(string columnName, string value) {
    cout << "storing: " << value << endl;
    //columns[columnName].value = value;
    columns[columnName] = value;
    columns[columnName].isNull = false;
    return this;
  }

  Model *Model::Set(string columnName, const char *newValue) {
    columns[columnName].isNull = true;
    if (newValue != NULL) {
      stringstream ss(newValue);
      columns[columnName] = ss.str();
      columns[columnName].isNull = false;
    }
    return this;
  }
  
  string Model::GenerateSql() {
    string result = "";
    if (!isInserting) {
      if (columns.size() > 0) {
	stringstream columnsStr("");
	string foreignsStr = "";
	for (COLUMNS_ORDER_ITEM item : order) {
	  if (columnsStr.str() != "") {
	    columnsStr << ", ";
	  }
	  if (columns[item.second].foreign_key) {
	    foreignsStr += ", "						\
	      "FOREIGN KEY(" + item.second + ") "			\
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
	    (columns[item.second].auto_increment ? " AUTOINCREMENT" : "") <<
	    (columns[item.second].default_value != "" ? " DEFAULT " + columns[item.second].default_value : "") <<
	    (columns[item.second].not_null ? " NOT NULL" : "");
	}
	result += " (" + columnsStr.str() + foreignsStr + ")";
      }
    } else {
      string columnNames = "";
      string values = "";
      for (COLUMN col : columns) {
	if (col.second.value != "") {
	  columnNames += col.first + ", ";
	  values += "\"" + col.second.value + "\", ";
	}
      }
      result = "";
      if (columnNames != "") {
	result += "(" + columnNames.substr(0, columnNames.length() - 2) + ")";
	result += " VALUES (" + values.substr(0, values.length() - 2) + ")";
      }
      isInserting = false;
    }
    return result;
  }

  string &Model::operator ()(string columnName) {
    return columns[columnName.c_str()].value;
  }

  // COLUMN_DESC &Model::operator [](string columnName) {
  //   return columns[columnName.c_str()];
  // }
  
  // char *Model::operator [](string columnName) {
  //   return columns[columnName.c_str()].value.c_str();
  // }

  COLUMN_DESC &Model::operator [](string columnName) {
    return columns[columnName.c_str()];
  }

}
