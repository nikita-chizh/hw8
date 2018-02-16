#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>


std::unordered_map<std::string, int> name_cash;


enum class COLOR {
    WHITE, GREY, BLACK
};

template<class T>
class Vert {
private:
    //basic vert propertes
    T data;
    //since adjacent_list is unordered_set
    //we can add connection without fear of repeating
    std::unordered_set<int> adjacent_list;
    //for proper work
    COLOR color;
    int distance;
    int parent;
public:
    template<class U>
    friend
    class Graph;

    Vert() : adjacent_list(0), color(COLOR::WHITE),
             distance(0), parent(-1) {

    }

    explicit Vert(const T &data) : adjacent_list(0), color(COLOR::WHITE),
                                   distance(0), parent(-1), data(data) {

    }

    //
    void add_connection(int id) {
        adjacent_list.insert(id);
    }

    int dist() {
        return this->distance;
    }

    const std::unordered_set<int> &get_adj_list() {
        return adjacent_list;
    }

    bool operator<(const Vert& rhs) const
    {
        return data < rhs.data;  //assume that you compare the record based on a
    }

};

//
template<class T>
class Graph {
private:
    std::vector<Vert<T>> vertices;

public:
    Graph() = default;

    void bfs(int vert_id) {
        std::queue<int> grey_queues;
        grey_queues.push(vert_id);
        while (!grey_queues.empty()) {
            int grey_vert = grey_queues.front();
            for (auto &i : vertices[grey_vert].adjacent_list) {
                if (vertices[i].color == COLOR::WHITE) {
                    vertices[i].color = COLOR::GREY;
                    vertices[i].distance = vertices[grey_vert].distance + 1;
                    vertices[i].parent = grey_vert;
                    grey_queues.push(i);
                }
            }
            vertices[grey_vert].color = COLOR::BLACK;
            grey_queues.pop();
        }
    }

    unsigned int add_vert(Vert<T> &&vert) {
        vertices.push_back(vert);
        return vertices.size() - 1;
    }

    unsigned int add_vert(const Vert<T> &vert) {
        vertices.push_back(vert);
        return vertices.size() - 1;
    }

    void add_edge(int first, int second) {
        vertices[first].add_connection(second);
        vertices[second].add_connection(first);
    }

    void sort(){
        std::sort (vertices.begin(), vertices.end());
    }

    void show() {
        if(name_cash.find("Isenbaev") == name_cash.end()){
            for (int i = 0; i < vertices.size(); ++i) {
                std::cout<<vertices[i].data <<" "<<"undefined"<<std::endl;
            }
            return;
        }
        for (int i = 0; i < vertices.size(); ++i) {
            std::cout<<vertices[i].data <<" ";
            if(vertices[i].data != "Isenbaev" && vertices[i].distance == 0)
                std::cout<<"undefined";
            else
                std::cout<<vertices[i].distance;
            std::cout<< std::endl;
        }
    }
};

Graph<std::string> graph;

//name to graph index

template<typename Out>
void split(const std::string &s, char delim, Out result);

std::vector<std::string> split(const std::string &s, char delim);


std::pair<int, int> another_two(int i) {
    if (i == 0) {
        return {1, 2};
    }
    if (i == 1) {
        return {0, 2};
    }
    if (i == 2) {
        return {0, 1};
    }
};

void connect_if_exist(int fid, std::string &to_connect) {
    auto check = name_cash.find(to_connect);
    //if to_connect exists in graph
    if (check != name_cash.end()) {
        graph.add_edge(fid, check->second);
    }
}

//process next 3 words
void process(std::vector<std::string> &words) {
    unsigned int size = words.size();
    int vert_id;
    for (int i = 0; i < size; ++i) {
        //then got two connected names(team members)
        auto connected = another_two(i);
        std::string &word = words[i];
        //check if word is already in graph
        auto check = name_cash.find(word);
        //if not in
        if (check == name_cash.end()) {
            //add
            Vert<std::string> vert(word);
            vert_id = graph.add_vert(vert);
            //name_cash store both name and id in graph
            int inserted_id = name_cash.insert({word, vert_id}).first->second;
            //connect them if they exists
            connect_if_exist(inserted_id, words[connected.first]);
            connect_if_exist(inserted_id, words[connected.second]);
        } else {//if in graph
            //just connect it
            //insert nothing
            connect_if_exist(check->second, words[connected.first]);
            connect_if_exist(check->second, words[connected.second]);
        }
    }
}

int main() {
    std::string line;
    std::getline(std::cin, line);
    int num = std::stoi(line) + 1;
    int i = 0;
    while (std::getline(std::cin, line) && i < num) {
        std::vector<std::string> words = split(line, ' ');
        process(words);
        ++i;
    }
    if(i != 0) {
        auto is_check = name_cash.find("Isenbaev");
        if(is_check != name_cash.end()){
            graph.bfs(is_check->second);
        }else
            graph.bfs(0);
        graph.sort();
        graph.show();
    }
    return 0;
}


template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

