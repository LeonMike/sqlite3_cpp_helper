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

#include <Model.hpp>
#include <vector>

using namespace std;

namespace sqlite3_helper {

  class Table {
  private:
    bool   isInserting;
    string lastInsertionCommand;
    string lastExecutedCommand;

  protected:
    sqlite3 *Db;
    Model *tableModel;
    std::vector<Model> lastQueryResult;
    static int StaticCallback(void *objPtr, int argc, char **argv, char **azColName);

  public:
    Table();
    Table(sqlite3 *db, string name);
    Table(string name, Model *tableModel);
    Table(sqlite3 *db, string name, Model *tableModel);
    ~Table();

    string name;

    virtual int QueryCallback(int argc, char **argv, char **azColName);

    void Create();
    
    Table *NewRow();
    Table *Set(string column, int value);
    Table *Set(string column, bool value);
    Table *Set(string column, float value);
    Table *Set(string column, string value);
    Table *Set(string column, const char *value);
    Table *Save();
    Table *RetryLastSavingCommand();
    
    string GenerateSql();
    
    std::vector<Model> Get();
  };
  
}

