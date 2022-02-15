#ifndef IO_H
#define IO_H

#include <string>
#include <iostream>

class Command{
public:
    static std::string add;
    static std::string show;
    static std::string update;
    static std::string del;
    static std::string help;
};


bool isNumber(std::string& s);
void inputNumber(int& target, const std::string inMessage,  std::string errMessage ="the input is invalid (must be a number)!\n");

#endif