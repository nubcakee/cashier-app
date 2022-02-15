#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>


class Product{
protected:
  std::string m_name;
  int m_price;

public:
  std::string getName();
  int getPrice();

  void setName(std::string newName);
  void setPrice(int newPrice);

  Product(const std::string prodName, int prodPrice);

};

#endif
