#include <iostream>
#include "Database.hpp"

int main() {
  Database *db = new Database();
  
  delete db;
  return 0;
}
