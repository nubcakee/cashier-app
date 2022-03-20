#include "../headers/database.hpp"

Database::SqltDB::SqltDB(){
}

Database::SqltDB::~SqltDB(){
	sqlite3_close(DB);
}

void Database::SqltDB::open(const char* fileName){
    exit = sqlite3_open(fileName, &DB);

    if (exit) {
        std::cerr << "[ERROR] " << sqlite3_errmsg(DB) << std::endl;
    }
    // else
    //     std::cout << "Opened Database Successfully!" << std::endl;
}

// int Database::SqltDB::execute(std::string sql){
//       char* messageError;
//       exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
      
//       if (exit != SQLITE_OK) {
//         std::cerr << "[ERROR] " << std::string(messageError) << std::endl;
//         sqlite3_free(messageError);
//       }
//     //   else{
//     //          std::cout << "[SUCCESS] " << sql << std::endl;
//     //   }
         
//         // std::cout << "exit code " << exit << std::endl;
//         return exit;
// }


int Database::SqltDB::callbackShow(void* data, int argc, char** argv, char** azColName)
    {
        
        int i;
        std::vector<std::string> d;
        for (i = 0; i < argc; i++) {
            d.push_back( argv[i] ? argv[i] : "NULL");
        }
        callbackCout(d);
        return 0;
}

int Database::SqltDB::callbackFetchAll(void* data, int argc, char** argv, char** azColName)
    {
        Records* record  = static_cast<Records*>(data);
        
        int i;
        std::vector<std::string> d;
        for (i = 0; i < argc; i++) {
            d.push_back( argv[i] ? argv[i] : "NULL");
        }
        record->push_back(d);
        return 0;
}


int Database::SqltDB::execute(std::string query, int(*func)(void*, int, char**, char**)){
    records.clear();
    char* errorMessage; 
    exit = sqlite3_exec(DB, query.c_str(), func, &records, &errorMessage);
    if (exit != SQLITE_OK)
          std::cerr << "[ERROR] " << std::string(errorMessage) << std::endl;   
    sqlite3_free(errorMessage);
    return exit;
}



std::string Database::sql(const std::string sql, std::vector<std::string> args){
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


bool Database::SqltDB::isExist(std::string sql){
      this->execute(sql, this->callbackFetchAll);

      try{
          auto first = this->records[0][0];
      }
      
      catch( const std::length_error &e){
          return false;
      }

      catch (...){
          return false;
      }
    //   if (first == "NULL") return false;
      return true;
    }