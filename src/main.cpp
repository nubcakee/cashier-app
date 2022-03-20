#include "../headers/stock.hpp"
#include "../headers/io.hpp"
#include "../headers/database.hpp"

#include <vector>
#include <string>
#include <map>



static Database::SqltDB db;
static IO::Command command;


std::vector<std::string> columns = {"Id", "Product Name", "Price", "Quantity", "Total"};
std::vector<int> columnsWidth = {10,20,20,20,20};
static IO::DataDisplayer dataDisplayer(columns, columnsWidth);

void Database::SqltDB::callbackCout(std::vector<std::string>& dataFetch){        
        auto id = dataFetch[0];
        auto name = dataFetch[1];
        auto price = IO::priceFormat(dataFetch[2]);
        auto quantity = dataFetch[3];
        auto total = IO::priceFormat(dataFetch[4]);
        std::vector<std::string> data{id,name, price, quantity, total};
        dataDisplayer.drawBody(data);  
}





int main(){
  db.open("db.sqlite3");

 
  // db.execute("CREATE TABLE IF NOT EXISTS user (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT NOT NULL UNIQUE, password VARCHAR(20))");
  
  // db.execute("CREATE TABLE IF NOT EXISTS session (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL UNIQUE)");
  
  db.execute("CREATE TABLE IF NOT EXISTS stock (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL UNIQUE, price INTEGER NOT NULL, quantity INTEGER NOT NULL, total INTEGER NOT NULL)");
  
  
  while(true){

    std::cout << ">> ";
    std::getline(std::cin, command.inputBuffer);

    if (command == COMMAND_HELP) std::cout << HELP;
    
    else if (command == COMMAND_ADD){
      Stock s;
      std::cin >> s;
      std::string sql_c =  Database::sql("insert into stock(name, price, quantity, total) values(?,?,?,?)", {s.name, std::to_string(s.price), std::to_string(s.quantity), std::to_string(s.total)});
      db.execute(sql_c);
    }
    
    else if (command == COMMAND_SHOW){
      db.execute("SELECT SUM(total) from stock", Database::SqltDB::callbackFetchAll);
      auto total = db.records[0][0];
      if (total != "NULL"){
          total = IO::priceFormat(total);
      }
        
     
      dataDisplayer.drawHead();
      db.execute("SELECT * FROM stock", Database::SqltDB::callbackShow);
      dataDisplayer.drawLine();
      dataDisplayer.drawBelow(total, 5);
      //std::cout << dataDisplayer.totalWidth(); 
    
    }

    else if (command.inputBuffer.find(COMMAND_UPDATE) != std::string::npos){
      int id;
      try{
          id = std::stoi(command.getIdArgument());
      }
      
      catch(const std::out_of_range & e){
            std::cout << "no id was selected\n";
            continue;
      }
      catch(const std::invalid_argument & e){
            std::cout << "invalid argument\n";
            continue;
      }

      std::string sql_q = Database::sql("SELECT * FROM stock where id = ?", {std::to_string(id)});

      if (!db.isExist(sql_q)) {
        std::cout << "no stock with id of " << id << std::endl;
        continue;
      }

      
      
      // Records records;
      db.execute(sql_q, Database::SqltDB::callbackFetchAll);
      auto records = db.records;

      db.execute(sql_q, Database::SqltDB::callbackShow);
     
      
      if (records.empty()) continue;


      std::string name = records[0][1];
      unsigned int price = std::stoi(records[0][2]);
      unsigned int quantity = std::stoi(records[0][3]);
      
      
      IO::inputString(name, "New Name: ");
      IO::inputNumber(price, "NewPrice: ");
      IO::inputNumber(quantity, "New Quantity: ");
      unsigned int total = price * quantity;      
      sql_q = Database::sql("UPDATE stock SET name = ? , price = ? , quantity = ?, total = ? WHERE id = ?", {name, std::to_string(price), std::to_string(quantity), std::to_string(total), std::to_string(id)});
      db.execute(sql_q);
     }

    else if (command.inputBuffer.find(COMMAND_DELETE) != std::string::npos){
      int id;
      try{
          id = std::stoi(command.getIdArgument());
      }
      
      catch(const std::out_of_range & e){
            std::cout << "no id was selected del\n";
            continue;
      }
      catch(const std::invalid_argument & e){
            std::cout << "invalid argument\n";
            continue;
      }

      // check if exist
      auto sql_qSelect = Database::sql("SELECT * FROM stock where id = ?", {std::to_string(id)});

      if (!db.isExist(sql_qSelect)){
        std::cout << "no stock with id of " << id << "\n";
        continue;
      }


      std::string sql_qDelete =  Database::sql("DELETE FROM stock where id = ?", {std::to_string(id)});
      db.execute(sql_qDelete);
      std::cout << id << " deleted\n";
      
    }

    else if (command == COMMAND_EXIT) exit(0);
    else std::cout << HELP;

  }

}
