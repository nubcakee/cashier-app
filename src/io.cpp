#include "../headers/io.hpp"

bool IO::isNumber(std::string& s){
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) ++it;
  return !s.empty() && it == s.end();
}

void IO::inputNumber(unsigned int& target, const std::string inMessage, std::string errMessage){
    while(true){
        std::string temp;
        std::cout << inMessage;
        std::getline(std::cin, temp);
        if (temp.empty()){
            break;
        }
        if (!isNumber(temp)){
            std::cerr << errMessage;
        }
        else{
            try{
            target = std::stoi(temp);
            }

            catch (const std::out_of_range & e) {
            std::cerr << "Number is too large!\n";
            continue;
        }
        break;
      }
  }
}

void IO::inputString(std::string& target, const std::string inMessage){
    std::string temp;
    std::cout << inMessage;
    std::getline(std::cin, temp);
    if(!temp.empty()){
        target = temp;
    }
}

std::string IO::truncateByEllipsis(std::string target, int maxSize){
    if (target.length() > maxSize){
        return target.substr(0,maxSize-3) + "...";
    }
    return target;
};


IO::Command::Command(){

}

bool IO::Command::operator == (const std::string &r){
        return this->inputBuffer == r;
}

std::string IO::Command::getIdArgument(){
        std::string idString; 
        std::string::const_iterator it = this->inputBuffer.begin();
         while (it != this->inputBuffer.end()) {
             if (std::isdigit(*it)){
                    idString += *it;
             }
             ++it;
         }
        return idString;
    }

std::string IO::priceFormat(std::string target){
    size_t targetSize = target.size() - 1;
    int c = 0;
    for(size_t i = targetSize; i > 0;i--){
            c++;
            if (c % 3 == 0 && i != 0){
                target.insert(i, ".");
                c = 0;
            }
    }
    // std::cout << target;
    return target;
}   

IO::Fields::Fields(std::vector<std::string>& label, std::vector<int>& labelWidth){
        if (label.size() != labelWidth.size()){
            throw std::out_of_range("Invalid fields dimension, found mismatch size");
        }
        for(size_t i = 0; i< label.size();i++){
                    columns.push_back(label[i]);
                    columnsWidth.push_back(labelWidth[i]);
        }
};

std::tuple <std::string, int> IO::Fields::getField(int index){
       return std::make_tuple(columns[index], columnsWidth[index]);
}

int IO::Fields::size(){
        return columns.size();
} 

IO::DataDisplayer::DataDisplayer(std::vector<std::string>& label, std::vector<int>&labelWidth)
    :m_fields{label, labelWidth}{
    sep = " |";
    generateLine();
}

int IO::DataDisplayer::numFields(){
        return m_fields.size();
};


int IO::DataDisplayer::totalWidth(){
        int width = m_fields.size() * sep.size();
        for (size_t i = 0; i < m_fields.size();i++){
            std::string label;
            int labelWidth;
            std::tie(label, labelWidth) = m_fields.getField(i);
            width += labelWidth;
        }
        // std::map<std::string, int>::iterator it;
        
        // for (it = m_fields.begin(); it != m_fields.end(); it++){
        //     width += it->second;
        // }
        return width;
};

void IO::DataDisplayer::generateLine(){
        line = sep + std::string(totalWidth() -1, '-') + '|';
};

void IO::DataDisplayer::drawLine(){
    std::cout << line;
}

void IO::DataDisplayer::drawHead(){
    std::cout << "\n\n" << line << '\n' << sep;

    for (size_t i = 0; i < m_fields.size();i++){
        std::string label;
        int colWidth;
        std::tie(label, colWidth) = m_fields.getField(i);
        std::cout << std::setw(colWidth) << label << sep;
    }

    std::cout << "\n" << line << "\n";

    // std::map<std::string, int>::iterator it;
    // for (it = m_fields.begin(); it != m_fields.end(); it++){
    //     std::cout << std::setw(it->second) << it->first << sep;
    // }
    
}

void IO::DataDisplayer::drawBody(std::vector<std::string> &dataFetch){
    for (size_t i = 0; i< m_fields.size();i++){
        std::string column;
        int columnWidth;
        std::tie(column, columnWidth) = m_fields.getField(i);
        auto data = truncateByEllipsis(dataFetch[i], columnWidth);
        std::cout << sep << std::setw(columnWidth) << data;
    }
    // std::map<std::string, int>::iterator it;
    // int index = 0;
    // for (it =m_fields.begin(); it != m_fields.end();it++){
    //     auto data = truncateByEllipsis(dataFetch[index], it->second);
    //     std::cout << sep << std::setw(it->second) << data;
    //     index++;
    // }
  
    std::cout << std::endl; 
}   