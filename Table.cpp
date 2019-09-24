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

#include <Table.hpp>
#include <sstream>
#include <iostream>
#include <assert.h>

using namespace std;

namespace sqlite3_cpp_helper_v2 {

  Table::Table() {}
  Table::Table(sqlite3 *db, string name): Db(db), name(name) {}
  Table::Table(string name, Model* recordModel): name(name), tableModel(recordModel) {}
  Table::Table(sqlite3 *db, string tableName, Model* tableModelToSave): Db(db) { name = tableName; tableModel = tableModelToSave; }

  int Table::CallbackHelper(void *objPtr, int argc, char **argv, char **azColName) {
    return ((Table *)objPtr)->QueryCallback(argc, argv, azColName);
  }

  int Table::QueryCallback(int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
      cout << "" << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    return 0;
  }
  
  // Table::Table(sqlite3 *db): Db(db) {}
  // Table::Table(Table &base): Db(base.Db) {}
  // Table::Table(string tableName) { name = tableName; }
  // // Table::Table(const char *tableName) { name = tableName; }
  // Table::~Table() { /*sqlite3_close(Db); columns.clear();*/ }

  void Table::Create() {
    char *zErrMsg = 0;
    isInserting = false;
    assert(tableModel != NULL);
    assert(Db != NULL);
    cout << "\033[1;33mEXECUTING:\033[1;36m " << GenerateSql() << "\033[0;0m" << endl;
    int rc = sqlite3_exec(Db, GenerateSql().c_str(), NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
      cout << "\033[4;31mSQL Error: " << zErrMsg << "\033[0;0m" << endl;
    }
  }
  
  Table *Table::NewRow() {
    isInserting = true;
    tableModel->New();
    return this;
  }
  
  Table *Table::Set(string column, int value) {
    tableModel->Set(column, value);
    return this;
  }

  Table *Table::Set(string column, bool value) {
    tableModel->Set(column, value);
    return this;
  }
  
  Table *Table::Set(string column, float value) {
    tableModel->Set(column, value);
    return this;
  }

  Table *Table::Set(string column, string value) {
    tableModel->Set(column, value);
    return this;
  }

  Table *Table::Set(string column, const char *value) {
    tableModel->Set(column, value);
    return this;
  }

  Table *Table::Save() {
    char *zErrMsg = 0;
    if (lastInsertionCommand != "") {
      cout << lastInsertionCommand << endl;
      int rc = sqlite3_exec(Db, lastInsertionCommand.c_str(), NULL, NULL, &zErrMsg);
      if (rc != SQLITE_OK) {
	cout << "SQL Error: " << zErrMsg << endl;
      }
    }
    return this;
  }

  // string Table::sqlSave() {
  //   string result = "INSERT INTO " + name + " VALUES";
  //   if (columns.size() > 0) {
  //     stringstream columnsStr("");
  //     /*for (COLUMN col : columns) {
  // 	cout << "Col (" << col.first << ")" << endl <<
  // 	  "\ttype:\t" << col.second.type << endl <<
  // 	  "\tmax_length:\t" << col.second.max_length << endl <<
  // 	  "\tprimary_key:\t" << col.second.primary_key << endl <<
  // 	  "\tnot_null:\t" << col.second.not_null << endl <<
  // 	  "\tdefault_value:\t" << col.second.default_value << endl <<
  // 	  "\tvalue:\t" << col.second.value << endl <<
  // 	  "\tforeign_key:\t" << col.second.foreign_key << endl <<
  // 	  "\treference_table:\t" << col.second.reference_table << endl <<
  // 	  "\treference_colum:\t" << col.second.reference_column << endl;
  //     }*/
  //     for (COLUMNS_ORDER_ITEM item : order) {
  // 	if (columnsStr.str() != "") {
  // 	  columnsStr << ", ";
  // 	}
  // 	if (!columns[item.second].isNull) {
  // 	  if (columns[item.second].type == "TEXT" ||
  // 	      columns[item.second].type.substr(0, 7) == "VARCHAR" ||
  // 	      columns[item.second].type == "DATE") {
  // 	    columnsStr << "'" << columns[item.second].value << "'";
  // 	  } else
  // 	    columnsStr << columns[item.second].value;
  // 	} else {
  // 	  columnsStr << "NULL";
  // 	}
  //     }
  //     result += " (" + columnsStr.str() + ")";
  //   }
  //   return result;
  // }
  
  string Table::GenerateSql() {
    assert(tableModel != NULL);
    string result = "";
    if (!isInserting) {
      result = "CREATE TABLE " + name;
      if (tableModel->ColumnsCount() > 0) {
	result += tableModel->GenerateSql();
      }
    } else {
      result = "INSERT INTO " + name + " ";
      result += tableModel->GenerateSql();
      lastInsertionCommand = result;
      isInserting = false;
    }
    return result + ";";
  }

  void Table::Get() {
    char *zErrMsg = 0;
    int rc = sqlite3_exec(Db, ("SELECT * FROM " + name).c_str(), Table::CallbackHelper, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
      cout << "Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
    }
  }

  // COLUMN_DESC &Table::operator [](string name) {
  //   return columns[name.c_str()];
  // }

}
