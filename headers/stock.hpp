#ifndef STOCK_H
#define STOCK_H

#include "io.hpp"

class Stock{
public:
    Stock();
    std::string name;
    unsigned int price;
    unsigned int quantity;
    unsigned int total;
    friend std::istream & operator >> (std::istream &in, Stock& s);
    void updateStock();
    void updateTotal();
};

#endif
