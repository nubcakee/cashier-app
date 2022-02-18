#include "../headers/database.hpp"

SqltDB::SqltDB(){
}

SqltDB::~SqltDB(){
	sqlite3_close(DB);
}

void SqltDB::open(const char* fileName){
    exit = sqlite3_open(fileName, &DB);

    if (exit) {
        std::cerr << "[ERROR] " << sqlite3_errmsg(DB) << std::endl;
    }
    // else
    //     std::cout << "Opened Database Successfully!" << std::endl;
}

int SqltDB::execute(std::string sql){
      char* messageError;
      exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
      
      if (exit != SQLITE_OK) {
        std::cerr << "[ERROR] " << std::string(messageError) << std::endl;
        sqlite3_free(messageError);
      }
    //   else{
    //          std::cout << "[SUCCESS] " << sql << std::endl;
    //   }
         
        // std::cout << "exit code " << exit << std::endl;
        return exit;
}

int SqltDB::callback(void* data, int argc, char** argv, char** azColName)
    {
        fetchOne.clear();
        int i;
        std::vector<std::string> d;
        for (i = 0; i < argc; i++) {
            // printf("%d\n", i);
            d.push_back( argv[i] ? argv[i] : "NULL");
            // printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        fetchOne = d;
        callbackCout(d);
        return 0;
    }


int SqltDB::query(std::string query){
    //   result.clear();
      std::string data;
      exit = sqlite3_exec(DB, query.c_str(), SqltDB::callback, (void*)data.c_str(), NULL);
    //   if (exit != SQLITE_OK)
    //       std::cerr << "[ERROR] " << query << std::endl;
    //   else {
    //       std::cout << "[SUCCESS] " << query << std::endl;
    //   }
       
    return exit;
}
// void SqltDB::callbackCout(std::vector<std::string>& dataFetch){};
std::vector<std::string> SqltDB::fetchOne = {};
std::string sql(const std::string sql, std::vector<std::string> args){
        int pos;
        int counter = 0;
        std::string x = sql;
        std::string old("?");
        while ((pos = x.find(old)) != std::string::npos){
                if (counter >= args.size()){
                  return "argument is'nt match\n";
                }
                x.replace(pos, old.length(), "\""+ args[counter]+ "\"");
                counter++;
        }
                return x;
}
