#include "../headers/product.hpp"
#include "../headers/stock.hpp"
#include "../headers/io.hpp"

#include <vector>
#include <map>
#include <string>

#define HELP "Command: \n \t add : Add Stock\n \t show: Display Stocks\n \t update: Update Stock\n \t delete: Delete Stock\n"

int main(){
  std::map<int, Stock> stockMap;

  while(true){
    std::string command;
    std::cout << ">> ";
    std::getline(std::cin, command);
    if (command == "help") std::cout << HELP;
    else if (command == "add"){
      Stock s;
      std::cin >> s;
      s.setId(stockMap.size() + 1);
      stockMap.insert({stockMap.size() + 1, s});
    }
    else if (command == "show"){
      std::cout << stockMap;
    }

    else if (command == "update"){
      int id;
      inputNumber(id,"Enter id : ");
      auto it  = stockMap.find(id);
      if (it != stockMap.end()){
        std::cout << it->second;
        std::cout << "updating " << it->second.getName() << std::endl;
        std::cin >> it->second;
      }
      else std::cout << "id not found\n";
    }

    else if (command == "delete"){
      int id;
      inputNumber(id,"Enter id : ");
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
