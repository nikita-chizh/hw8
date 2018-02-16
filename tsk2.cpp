#include <iostream>
#include <unordered_set>

int main() {
    std::unordered_set<std::string> checking_set;
    std::unordered_set<std::string> spamers;
    std::string line;
    std::getline(std::cin, line);
    int num = std::stoi(line) ;
    int i = 0;
    spamers.reserve(num);
    while(std::getline(std::cin, line) && i < num){
        auto check = checking_set.insert(line);
        if(!check.second){
            spamers.insert(line);
        }
        ++i;
    }
    for(const auto& ref: spamers){
        std::cout<<ref<<std::endl;
    }
    return 0;
}