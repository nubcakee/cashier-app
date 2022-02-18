#ifndef STOCK_H
#define STOCK_H

#include "io.hpp"

class Stock{
public:
    Stock(){};
    std::string name;
    int price;
    int quantity;
    friend std::istream & operator >> (std::istream &in, Stock& s);
    void updateStock();
};

#endif
