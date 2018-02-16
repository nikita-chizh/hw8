#include <iostream>
#include <unordered_map>
#include <vector>

using Simple_Dict = std::unordered_map<char , std::vector<std::string>>;

void show_letter(const Simple_Dict& dict, char key){
    const auto& words = dict.find(key) -> second;
    for(const auto& ref: words){
        std::cout<<ref<<std::endl;
    }
}

int main() {
    Simple_Dict dict;
    for(char c = 'a'; c < '{'; ++c){
        dict.insert({c, {}});
    }
    std::string line;
    char key;
    std::getline(std::cin, line);
    int num = std::stoi(line) + 1;
    int i = 0;
    while(std::getline(std::cin, line) && i < num){
        if(line.length() == 2){
            char ins_key = line[0];
            auto& words = dict.find(ins_key)->second;
            words.push_back(line);
        } else if(line.length() == 1){
            key = line[0];
        }
        ++i;
    }
    show_letter(dict, key);
    return 0;
}

7
Ayzenshteyn Oparin Samsonov
Isenbaev Oparin Toropov
Ayzenshteyn Chevdar Samsonov
Fominykh Isenbaev Oparin
Dublennykh Fominykh Ivankov
Burmistrov Dublennykh Kurpilyanskiy
Cormen Leiserson Rivest



Ayzenshteyn 2
Burmistrov 3
Chevdar 3
Cormen undefined
Dublennykh 2
Fominykh 1
Isenbaev 0
Ivankov 2
Kurpilyanskiy 3
Leiserson undefined
Oparin 1
Rivest undefined
Samsonov 2
Toropov 1