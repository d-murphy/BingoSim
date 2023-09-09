#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <iterator>

const int POSS_COL_NUMS = 15; 

auto rng = std::default_random_engine(); 

std::vector<int> getPossibleSpace(int start){
    std::vector<int> options; 
    for(int i = 0; i < POSS_COL_NUMS; i++) {
        options.push_back(start + i); 
    }
    return options; 
}

std::vector<int> selectNRandom(int start, int n){
    std::vector<int> options = getPossibleSpace(start);     
    std::shuffle(options.begin(), options.end(), rng); 
    return std::vector<int>(options.begin(), options.begin() + n); 
}

std::map<int, bool> convertToMap(std::vector<int> spaces){
    std::map<int, bool> m; 
    for(int i: spaces) {
        m[i] = false; 
    }; 
    return m; 
}

std::vector<std::map<int,bool>> makeCard(){
    std::vector<std::map<int, bool>> card; 
    std::vector<int> starts {1, 16, 31, 46, 61}; 
    for (int i = 0; i < starts.size(); i++){
        int spacesNeeded = i == 2 ? 4 : 5; 
        std::vector<int> spaces = selectNRandom(starts[i], spacesNeeded); 
        card.push_back(convertToMap(spaces)); 
    }; 
    return card; 
}

class Card {
    public: 
        Card() {
            card = makeCard(); 
        }
        void Print(){
            std::cout << "here are the spaces: " << std::endl;
            for(auto col: card) {
                auto it = col.begin(); 
                while(it != col.end()){
                    std::cout << it->first << " " << it->second << std::endl; 
                    it++; 
                }; 
                std::cout << std::endl; 
            }
            std::cout << std::endl;   
        }
    private: 
        std::vector<std::map<int, bool>> card;

};



int main(){
    Card myCard; 
    std::cout << std::endl; 
    myCard.Print(); 
    return 0; 
}