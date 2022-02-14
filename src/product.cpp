#include "../headers/product.hpp"

Product::Product(const std::string prodName, int prodPrice)
    :m_name{prodName},
    m_price{prodPrice}{}

std::string Product::getName(){
    return m_name;
}

int Product::getPrice(){
  return m_price;
}

void Product::setPrice(int newPrice){
    m_price = newPrice;
}

void Product::setName(std::string newName){
  m_name = newName;
}