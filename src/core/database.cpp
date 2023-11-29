#include "database.hpp"

#include <sqlite3.h>

#include <cstring>
#include <iostream>
#include <string>

void createTables() {
  sqlite3 *db;
  sqlite3_open(getenv("DATABASE"), &db);

  char *err = 0;
  std::string sql_tables =
      "CREATE TABLE user ("
      "username VARCHAR(100) PRIMARY KEY,"
      "password VARCHAR(100) NOT NULL); ";
  sql_tables +=
      "CREATE TABLE task ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
      "title VARCHAR(100) NOT NULL, "
      "username VARCHAR(100) NOT NULL, "
      "description VARCHAR(500), "
      "delivery_date DATE, "
      "is_finished BOOLEAN NOT NULL DEFAULT(false), "
      "FOREIGN KEY(username) REFERENCES user(username));";

  int rc = sqlite3_exec(db, sql_tables.c_str(), nullptr, nullptr, &err);
  if (rc != SQLITE_OK) {
    std::cout << "SQL error: " << err << std::endl;
    sqlite3_free(err);
  } else {
    std::cout << "SUCESS!\n";
  }

  sqlite3_close(db);
}