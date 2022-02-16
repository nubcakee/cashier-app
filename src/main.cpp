#include "../headers/product.hpp"
#include "../headers/stock.hpp"
#include "../headers/io.hpp"
#include "../headers/database.hpp"

#include <vector>
#include <map>
#include <string>

#define HELP "Command: \n \t add : Add Stock\n \t show: Display Stocks\n \t update {id}: Update Stock by id\n \t delete {id}: Delete Stock by id\n"
std::string Command::add = "add";
std::string Command::show = "show";
std::string Command::update = "update";
std::string Command::del = "delete";
std::string Command::help = "help";

static std::map<int, Stock> stockMap;
SqltDB db;

int main(){  
  db.open("db.sqlite3");
  db.execute("CREATE TABLE IF NOT EXISTS stock (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL UNIQUE, price INTEGER NOT NULL, quantity INTEGER NOT NULL)");
  while(true){
    Stock s;
    std::string command;
    std::cout << ">> ";
    std::getline(std::cin, command);
    if (command == Command::help) std::cout << HELP;
    else if (command == Command::add){
      Stock s;
      std::cin >> s;
      s.setId(stockMap.size() + 1);
      std::string sql_c =  sql("insert into stock(name, price, quantity) values(?,?,?)", {s.getName(), std::to_string(s.getPrice()), std::to_string(s.getQuantity())});
      // std::cout << sql_c;
      db.execute(sql_c);
      // stockMap.insert({stockMap.size() + 1, s});
    }
    else if (command == Command::show){
      std::cout << stockMap;
    }

    else if (command.find(Command::update) != std::string::npos){
      int id;
      try{
          id = std::stoi(command.substr(Command::update.length() + 1, command.length()));
      }
      
      catch(const std::out_of_range & e){
            std::cout << "no id was selected\n";
            continue;
      }
      catch(const std::invalid_argument & e){
            std::cout << "invalid argument\n";
            continue;
      }

      auto it  = stockMap.find(id);
      if (it != stockMap.end()){
        std::cout << it->second;
        std::cout << "updating " << it->second.getName() << std::endl;
        it->second.updateStock();
      }
      else std::cout << "id not found\n";
    }

    else if (command.find(Command::del) != std::string::npos){
      int id;
      try{
          id = std::stoi(command.substr(Command::del.length() + 1, command.length()));
      }
      
      catch(const std::out_of_range & e){
            std::cout << "no id was selected del\n";
            continue;
      }
      catch(const std::invalid_argument & e){
            std::cout << "invalid argument\n";
            continue;
      }


      auto it  = stockMap.find(id);
      if (it != stockMap.end()){
        stockMap.erase(it);
        std::cout << id << " is deleted\n";
      }
      else std::cout << "id not found\n";
    }

    else std::cout << HELP;

  }

}
