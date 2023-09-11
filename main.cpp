#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <iterator>

const int POSS_COL_NUMS = 15; 

auto rng = std::default_random_engine(); 

std::vector<int> getPossibleSpace(int start, int possSpcCt){
    std::vector<int> options; 
    for(int i = 0; i < possSpcCt; i++) {
        options.push_back(start + i); 
    }
    return options; 
}

std::vector<int> selectNRandom(int start, int n, int possSpcCt){
    std::vector<int> options = getPossibleSpace(start, possSpcCt);     
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
        std::vector<int> spaces = selectNRandom(starts[i], spacesNeeded, POSS_COL_NUMS); 
        auto newMap = convertToMap(spaces); 
        card.push_back(newMap); 
    }; 
    return card; 
}

class Card {
    public: 
        Card() {
            card = makeCard(); 
        }
        void Print(){
            for(auto & col: card) {
                auto it = col.begin(); 
                while(it != col.end()){
                    std::cout << it->first << " " << it->second << std::endl; 
                    it++; 
                }; 
                std::cout << std::endl; 
            }
        }
        void markSpace(int numberCalled){
            int col = std::floor((numberCalled - 1) / 15); 
            auto & colMap = card[col]; 
            if(colMap.count(numberCalled)){
//                std::cout << "You got one!" << std::endl; 
                colMap[numberCalled] = true; 
            }
        }
    private: 
        std::vector<std::map<int, bool>> card;

};

class Round {
    public: 
        Round(int numCards) {
            for(int i=1; i<=numCards; i++){
                Card newCard; 
                cards.push_back(newCard); 
            }
            numbersCalled = selectNRandom(1, 75, 75); 
            spacesCalled = 0; 
        }
        void callNumber(){
            int numCalled = numbersCalled.back(); 
//            std::cout << "The next number is: " << numCalled << std::endl; 
            for(auto & card: cards){
                card.markSpace(numCalled); 
            }; 
            numbersCalled.pop_back(); 
            spacesCalled++; 
        }
        void printCards(){
            for(auto & card: cards){
                std::cout << "Next card: " << std::endl; 
                card.Print(); 
            }; 
        }
        void printNumbersCalled(){
            for(auto num: numbersCalled){
                std::cout << "number called: " << num << std::endl; 
            }
        }
        int getNumSpacesCalled(){
            return spacesCalled; 
        }
    private: 
        std::vector<Card> cards; 
        std::vector<int> numbersCalled; 
        bool isSolved; 
        int spacesCalled; 
}; 



int main(){
    std::cout << std::endl; 
    Round round(3); 
    round.callNumber(); 
    round.callNumber(); 
    round.callNumber(); 
    round.callNumber(); 
    round.callNumber(); 
    round.callNumber(); 
    round.callNumber(); 
    round.callNumber(); 
    round.callNumber(); 
    round.callNumber(); 
    round.callNumber(); 
    round.callNumber(); 
    round.callNumber(); 
    round.callNumber(); 
    round.printCards(); 
    std::cout << "After " << round.getNumSpacesCalled() << " called." << std::endl; 
    // Card myCard; 
    // myCard.Print(); 
    return 0; 
}