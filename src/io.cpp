#include "../headers/io.hpp"

bool isNumber(std::string& s){
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) ++it;
  return !s.empty() && it == s.end();
}

void inputNumber(int& target, const std::string inMessage, std::string errMessage){
    while(true){
        std::string temp;
        std::cout << inMessage;
        std::getline(std::cin, temp);
        if (!isNumber(temp)){
            std::cout << errMessage;
        }
        else{
            try{
            target = std::stoi(temp);
            }

            catch (const std::out_of_range & e) {
            std::cout << "Number is too large!\n";
            continue;
        }
        
        break;
      }
  }
}


