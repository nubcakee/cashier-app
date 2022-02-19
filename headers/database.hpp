#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <string>
#include <cstdarg>

using Record = std::vector<std::string>;
using Records = std::vector<Record>;

class SqltDB{
    sqlite3* DB;
    int exit;

public:
  static void callbackCout(std::vector<std::string>& dataFetch);
  SqltDB();
  ~SqltDB();
  void open(const char* fileName);
  int execute(std::string sql);
  static int callback(void* data, int argc, char** argv, char** azColName);
  Records query(std::string query);
};

std::string sql(const std::string sql, std::vector<std::string> args);

#endif
