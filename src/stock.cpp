#include "../headers/stock.hpp"



std::istream & operator >> (std::istream &in, Stock& s){
    inputString(s.name, "Name: ");
    inputNumber(s.price, "Price: ");
    inputNumber(s.quantity, "Quantity: ");
    return in;
}

