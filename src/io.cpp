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
        if (temp.empty()){
            break;
        }
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

void inputString(std::string& target, const std::string inMessage){
    std::string temp;
    std::cout << inMessage;
    std::getline(std::cin, temp);
    if(!temp.empty()){
        target = temp;
    }
}

std::string truncateByEllipsis(std::string target, int maxSize){
    if (target.length() > maxSize){
        return target.substr(0,maxSize-3) + "...";
    }
    return target;
};

std::string Command::add = "add";
std::string Command::show = "show";
std::string Command::update = "update";
std::string Command::del = "delete";
std::string Command::help = "help";

Command::Command(){

}

bool Command::operator == (const std::string &r){
        return this->inputBuffer == r;

}

std::string Command::getIdArgument(){
        std::string idString; 
        std::string::const_iterator it = this->inputBuffer.begin();
         while (it != this->inputBuffer.end()) {
             if (std::isdigit(*it)){
                    idString += *it;
             }
             ++it;
         }
        return idString;
    }
