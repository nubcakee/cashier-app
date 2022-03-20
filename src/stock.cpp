#include "../headers/stock.hpp"

Stock::Stock(){
    price = 0;
    quantity = 0;
}

void Stock::updateTotal(){
    this->total = this->price * this-> quantity;
}

std::istream & operator >> (std::istream &in, Stock& s){
    IO::inputString(s.name, "Name: ");
    IO::inputNumber(s.price, "Price: ");
    IO::inputNumber(s.quantity, "Quantity: ");
    s.updateTotal();
    return in;
}

void Stock::updateStock(){
    IO::inputString(this->name, "New Name: ");
    IO::inputNumber(this->price, "Price: ");
    IO::inputNumber(this->quantity, "Quantity: ");
    this->updateTotal();
}
