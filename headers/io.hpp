#ifndef IO_H
#define IO_H

#include <string>
#include <iostream>

bool isNumber(std::string& s);
void inputNumber(int& target, const std::string inMessage,  std::string errMessage ="the input is invalid (must be a number)!\n");

#endif