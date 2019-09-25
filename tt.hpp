#pragma once

#include <Database.hpp>

class ta: public sqlite3_cpp_helper_v2::Table {
public:
  ta(sqlite3 *db);

  //int QueryCallback(int argc, char **argv, char **azColName);
};

class tt: public sqlite3_cpp_helper_v2::Database {
public:
  tt(string dbName);
};
