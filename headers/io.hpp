#ifndef IO_H
#define IO_H

#include <string>
#include <iostream>
#include <iomanip>

#define HELP "Command: \n \t add : Add Stock\n \t show: Display Stocks\n \t update {id}: Update Stock by id\n \t delete {id}: Delete Stock by id\n \t exit : exit application\n"

#define COMMAND_ADD "add"
#define COMMAND_SHOW "show"
#define COMMAND_UPDATE "update"
#define COMMAND_DELETE "delete"
#define COMMAND_HELP "help"
#define COMMAND_EXIT "exit"

class Command{
public:
    Command();
    // static std::string add;
    // static std::string show;
    // static std::string update;
    // static std::string del;
    // static std::string help;
    std::string inputBuffer;
    bool operator == (const std::string &r);
    std::string getIdArgument();
};

bool isNumber(std::string& s);
void inputNumber(int& target, const std::string inMessage,  std::string errMessage ="the input is invalid (must be a number)!\n");
void inputString(std::string& target, const std::string inMessage);
std::string truncateByEllipsis(std::string target, int maxSize);

#endif