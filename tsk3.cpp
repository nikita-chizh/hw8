#include <iostream>
#include <unordered_set>

int main() {
    std::unordered_set<std::string> profesor_dates;
    std::string line;
    std::getline(std::cin, line);
    int num = std::stoi(line) ;
    int i = 0;
    profesor_dates.reserve(num);
    while(std::getline(std::cin, line) && i < num){
        profesor_dates.insert(line);
        ++i;
    }
    num = std::stoi(line) ;
    int mark = 0;
    i = 0;
    while(std::getline(std::cin, line) && i < num){
        if(profesor_dates.find(line) != profesor_dates.end()){
            ++mark;
        }
        ++i;
    }
    std::cout<<mark;
    return 0;
}