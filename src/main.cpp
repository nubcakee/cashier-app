#include "../headers/stock.hpp"
#include "../headers/io.hpp"
#include "../headers/database.hpp"

#include <vector>
#include <string>



const int id_width = 5;
const int name_width = 20;
const int int_width = 10;
const int num_flds = 5;
const std::string sep = " |" ;
const int total_width = id_width + name_width + int_width *3 + sep.size() * num_flds ;
const std::string line = sep + std::string( total_width-1, '-' ) + '|' ;

void SqltDB::callbackCout(std::vector<std::string>& dataFetch){
        auto id = dataFetch[0];
        auto name = dataFetch[1];
        auto price = dataFetch[2];
        auto quantity = dataFetch[3];
        auto total = dataFetch[4];  
        std::cout << sep
                << std::setw(id_width) << id<< sep  
                << std::setw(name_width) << truncateByEllipsis(name, name_width) << sep 
                << std::setw(int_width) << price << sep
                << std::setw(int_width) << quantity << sep
                << std::setw(int_width) << total << sep 
                << "\n";
 }

static SqltDB db;
static Command command;

int main(){
  db.open("db.sqlite3");
  db.execute("CREATE TABLE IF NOT EXISTS stock (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL UNIQUE, price INTEGER NOT NULL, quantity INTEGER NOT NULL, total INTEGER NOT NULL)");
  while(true){

    std::cout << ">> ";
    std::getline(std::cin, command.inputBuffer);

    if (command == COMMAND_HELP) std::cout << HELP;
    
    else if (command == COMMAND_ADD){
      Stock s;
      std::cin >> s;
      std::string sql_c =  sql("insert into stock(name, price, quantity, total) values(?,?,?,?)", {s.name, std::to_string(s.price), std::to_string(s.quantity), std::to_string(s.total)});
      db.execute(sql_c);
    }
    
    else if (command == COMMAND_SHOW){
      db.query("SELECT SUM(total) from stock", SqltDB::callbackFetchAll);
      auto total = db.records[0][0];    
      std::cout << "\n\n" << line << '\n' << sep
                << std::setw(id_width) << "Id" << sep
                << std::setw(name_width) << "Product Name" << sep
                << std::setw(int_width) << "Price" << sep 
                << std::setw(int_width) << "Quantity" << sep
                << std::setw(int_width) << "Total" << sep  
                << '\n' << line << "\n" ;
     
      db.query("SELECT * FROM stock", SqltDB::callbackShow);
      std::cout << line << '\n'
      << sep
      << std::setw(id_width) << "" << "  " 
      << std::setw(name_width) << "" << "  "
      << std::setw(int_width * 2) << "" << "  " << sep 
      << std::setw(int_width) << total << sep
      << "\n" <<  line <<"\n";
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
      std::cout << "\n\n*Selected\n";
      std::cout << line << '\n' << sep
                << std::setw(int_width) << "Id" << sep
                << std::setw(name_width) << "Product Name" << sep
                << std::setw(int_width) << "Price" << sep 
                << std::setw(int_width) << "Quantity" << sep 
                << '\n' << line << "\n" ;
      std::string sql_q = sql("SELECT * FROM stock where id = ?", {std::to_string(id)});

      // Records records;
      db.query(sql_q, SqltDB::callbackFetchAll);
      auto records = db.records;
      std::cout << std::setw(total_width) << ".....\n";
      
      if (records.empty()) continue;

      std::cout << records.size();

      std::string name = records[0][1];
      unsigned int price = std::stoi(records[0][2]);
      unsigned int quantity = std::stoi(records[0][3]);
      
      inputString(name, "New Name: ");
      inputNumber(price, "New Number: ");
      inputNumber(quantity, "New Quantity: ");      
      sql_q = sql("UPDATE stock SET name = ? , price = ? , quantity = ? WHERE id = ?", {name, std::to_string(price), std::to_string(quantity), std::to_string(id)});
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

      std::string sql_q =  sql("DELETE FROM stock where id = ?", {std::to_string(id)});
      db.execute(sql_q);
    }

    else if (command == COMMAND_EXIT) exit(0);
    else std::cout << HELP;

  }

}
