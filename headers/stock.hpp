#ifndef STOCK_H
#define STOCK_H

#include "product.hpp"
#include "io.hpp"
#include <iostream>
#include <vector>
#include <iomanip>
#include <vector>
#include <map>



class Stock: public Product{
  int m_quantity;
  int m_id;

public:
  Stock();
  Stock(std::string name, int price, int count, int id);
  int getQuantity();
  int getId();
  void setId(int id);
  void setQuantity(int newQuantity);
  friend std::ostream & operator << (std::ostream &out, Stock& s);
  friend std::istream & operator >> (std::istream &in, Stock& s);
};

void insertStock(std::string& name, int& price, int& quantity);
std::ostream & operator << (std::ostream &out, std::vector<Stock>& stockList);
std::ostream & operator << (std::ostream &out, std::map<int,Stock>& stockMap);

#endif
