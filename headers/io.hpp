#ifndef IO_H
#define IO_H

#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <vector>
#include <tuple>

#define HELP "Command: \n \t add : Add Stock\n \t show: Display Stocks\n \t update {id}: Update Stock by id\n \t delete {id}: Delete Stock by id\n \t exit : exit application\n"

#define COMMAND_ADD "add"
#define COMMAND_SHOW "show"
#define COMMAND_UPDATE "update"
#define COMMAND_DELETE "delete"
#define COMMAND_HELP "help"
#define COMMAND_EXIT "exit"

namespace IO{
class Command{
public:
    Command();
    std::string inputBuffer;
    bool operator == (const std::string &r);
    std::string getIdArgument();
};


class Fields{
    std::vector<std::string> columns;
    std::vector<int> columnsWidth;
public:
    Fields(std::vector<std::string>& label, std::vector<int>&labelWidth);
    std::tuple <std::string, int> getField(int index);
    int size();
};

class DataDisplayer{
private:
    Fields m_fields;
    std::string sep;
    
public:
    DataDisplayer(std::vector<std::string>& label, std::vector<int>&labelWidth);
    std::string line;
    int numFields();
    int totalWidth();
    void generateLine();
    void drawLine();
    void drawHead();
    void drawBody(std::vector<std::string>& dataFetch);
};

bool isNumber(std::string& s);
void inputNumber(unsigned int& target, const std::string inMessage,  std::string errMessage ="the input is invalid (must be a number)!\n");
void inputString(std::string& target, const std::string inMessage);
std::string truncateByEllipsis(std::string target, int maxSize);
std::string priceFormat(std::string target);

}
#endif