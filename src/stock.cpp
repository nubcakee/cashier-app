#include "../headers/stock.hpp"

Stock::Stock(){
    price = 0;
    quantity = 0;
}

void Stock::updateTotal(){
    this->total = this->price * this-> quantity;
}

std::istream & operator >> (std::istream &in, Stock& s){
    inputString(s.name, "Name: ");
    inputNumber(s.price, "Price: ");
    inputNumber(s.quantity, "Quantity: ");
    s.updateTotal();
    return in;
}

void Stock::updateStock(){
    inputString(this->name, "New Name: ");
    inputNumber(this->price, "Price: ");
    inputNumber(this->quantity, "Quantity: ");
    this->updateTotal();
}
