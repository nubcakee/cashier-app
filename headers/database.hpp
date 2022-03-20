#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <string>
#include <cstdarg>

using Record = std::vector<std::string>;
using Records = std::vector<Record>;



namespace Database{
  class SqltDB{
    sqlite3* DB;
    int exit;

  public:
    static void callbackCout(std::vector<std::string>& dataFetch);
  
    SqltDB();
    ~SqltDB();
    void open(const char* fileName);
    Records records;
    static int callbackShow(void* data, int argc, char** argv, char** azColName);
    static int callbackFetchAll(void* data, int argc, char** argv, char** azColName);
    int execute(std::string, int(*func)(void*, int, char**, char**)=NULL);
    bool isExist(std::string sql);
  };

  std::string sql(const std::string sql, std::vector<std::string> args);
}


#endif
