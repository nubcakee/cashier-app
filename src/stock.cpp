#include "../headers/stock.hpp"


Stock::Stock()
: Stock("",0,0,0){

}

Stock::Stock(std::string name, int price, int count, int id)
    :Product{name, price},
    m_quantity{count},
    m_id{id}
{}

int Stock::getQuantity(){
  return m_quantity;
};

int Stock::getId(){
  return m_id;
}

void Stock::setQuantity(int newQuantity){
  m_quantity = newQuantity;
}

void Stock::setId(int id){
    m_id = id;
}

void Stock::updateStock(){
  std::string temp;
  std::cout << "New Name: ";
  std::getline(std::cin, temp);
  if(!temp.empty()){
    this->setName(temp);
  }
  inputNumber(this->m_price, "New Price: ");
  inputNumber(this->m_quantity, "New Quantity: ");
}




std::istream & operator >> (std::istream &in, Stock& s){
      std::string temp;
      int intTemp = 0;
      while (temp.empty()){
          std::cout << "Name: ";
          std::getline(std::cin, temp);
      }
      s.setName(temp);
    inputNumber(intTemp, "Price: ");
    s.setPrice(intTemp);
    intTemp = 0;
    inputNumber(intTemp, "Quantity: ");
    s.setQuantity(intTemp);

    return in;
}

//cout stock;
std::ostream & operator << (std::ostream &out, Stock & s){
  std::cout << "----------------------------------------\n";
  std::cout << s.getId() << std::endl;
  std::cout << s.getName() << std::endl;
  std::cout << "Price: " << s.getPrice() << std::endl;
  std::cout << "Quantity: " << s.getQuantity() << std::endl;
  std::cout << "----------------------------------------\n";
  return out;
};


std::string truncateByEllipsis(std::string target, int maxSize){
    if (target.length() > maxSize){
        return target.substr(0,maxSize-3) + "...";
    }
    return target;
}
std::ostream & operator << (std::ostream &out, std::map<int,Stock>& stockMap){
   const int name_width = 20 ;
   const int int_width = 10 ;
   const int num_flds = 4 ;
   const std::string sep = " |" ;
   const int total_width = name_width + int_width *3 + sep.size() * num_flds ;
   const std::string line = sep + std::string( total_width-1, '-' ) + '|' ;

   std::cout << line << '\n' << sep
            << std::setw(int_width) << "Id" << sep
            << std::setw(name_width) << "Product Name" << sep
            << std::setw(int_width) << "Price" << sep 
            << std::setw(int_width) << "Quantity" << sep 
            << '\n' << line << "\n" ;

   for( auto &stock: stockMap)
   {
       std::cout << sep
                << std::setw(int_width) << stock.second.getId() << sep  
                << std::setw(name_width) << truncateByEllipsis(stock.second.getName(), name_width) << sep 
                << std::setw(int_width) << stock.second.getPrice() << sep
                << std::setw(int_width) << stock.second.getQuantity() << sep << "\n";
   }
   std::cout << line << '\n' ;
   return out;

}
std::ostream & operator << (std::ostream &out, std::vector<Stock> &stockList){
   const int name_width = 20 ;
   const int int_width = 10 ;
   const int num_flds = 4 ;
   const std::string sep = " |" ;
   const int total_width = name_width + int_width *3 + sep.size() * num_flds ;
   const std::string line = sep + std::string( total_width-1, '-' ) + '|' ;

   std::cout << line << '\n' << sep
            << std::setw(int_width) << "No" << sep
            << std::setw(name_width) << "Product Name" << sep
            << std::setw(int_width) << "Price" << sep 
            << std::setw(int_width) << "Count" << sep 
            << '\n' << line << "\n" ;

   for( auto &stock: stockList)
   {
       std::cout << sep
                << std::setw(int_width) << stock.getId() << sep  
                << std::setw(name_width) << truncateByEllipsis(stock.getName(), name_width) << sep 
                << std::setw(int_width) << stock.getPrice() << sep
                << std::setw(int_width) << stock.getQuantity() << sep << "\n";
   }
   std::cout << line << '\n' ;
   return out;
}