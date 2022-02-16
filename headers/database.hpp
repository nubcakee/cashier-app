#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <string>
#include <cstdarg>


typedef std::vector<std::vector<std::string>> vectorString;

class SqltDB{
    sqlite3* DB;
    int exit;

public:
  static vectorString result;
  SqltDB();
  ~SqltDB();
  void open(const char* fileName);
  int execute(std::string sql);
  static int callback(void* data, int argc, char** argv, char** azColName);
  void query(std::string query);
};

std::string sql(const std::string sql, std::vector<std::string> args);

#endif
