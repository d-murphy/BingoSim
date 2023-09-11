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

// std::map<int, bool> convertToMap(std::vector<int> spaces){
//     std::map<int, bool> m; 
//     for(int i: spaces) {
//         m[i] = false; 
//     }; 
//     return m; 
// }

std::vector<std::vector<int>> makeCard(){
    std::vector<std::vector<int>> card; 
    std::vector<int> starts {1, 16, 31, 46, 61}; 
    for (int i = 0; i < starts.size(); i++){
//        int spacesNeeded = i == 2 ? 4 : 5; 
        std::vector<int> spaces = selectNRandom(starts[i], 5, POSS_COL_NUMS); 
        card.push_back(spaces); 
    }; 
    return card; 
}

std::vector<std::vector<bool>> makeMakers(){
    std::vector<std::vector<bool>> markers {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,1,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
    }; 
    return markers; 
}

int getIndex(std::vector<int> v, int toFind){
    auto it = std::find(v.begin(), v.end(), toFind); 
    if (it != v.end()) {
        int index = it - v.begin(); 
        return index; 
    } else {
        return -1; 
    }
}

class Card {
    public: 
        Card() {
            card = makeCard(); 
            markers = makeMakers(); 
        }
        void Print(){
            
            for(int i = 0; i<5; i++) {
                for(int j=0; j<5; j++) {
                    bool marked = markers[j][i]; 
                    bool freeSpaceAdjust = i == 2 && j == 2; 
                    int space = card[j][i]; 
                    std::string text = freeSpaceAdjust ? "Free!" : std::to_string(space); 
                    std::string withHighlight = marked ?                 
                        "\033[1;31m" + text + "\033[0m" : text; 

                    std::cout << withHighlight << "\t" ; 
                }
                std::cout << std::endl; 
            }
            std::cout << std::endl; 
        }
        void markSpace(int numberCalled){
            int colInd = std::floor((numberCalled - 1) / 15); 
            auto col = card[colInd]; 
            int spaceInd = getIndex(col, numberCalled); 
            if(spaceInd >= 0){
                markers[colInd][spaceInd] = 1; 
            }
        }
        void countMarked(){
            int markedCt = 0; 
            for(auto col : markers){
                for(auto space: col){
                    if(space) markedCt++; 
                }
            }
            std::cout << "the marked count: " << markedCt << std::endl; 
        }
    private: 
        std::vector<std::vector<int>> card;
        std::vector<std::vector<bool>> markers; 
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
            std::cout << "The next number is: " << numCalled << std::endl; 
            for(auto & card: cards){
                card.markSpace(numCalled); 
            }; 
            numbersCalled.pop_back(); 
            spacesCalled++; 
        }
        void printCards(){
            for(auto & card: cards){
                card.countMarked(); 
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
    Round round(4); 
    round.callNumber(); 
    round.printCards(); 
    round.callNumber(); 
    round.printCards(); 
    round.callNumber(); 
    round.printCards(); 
    round.callNumber(); 
    round.printCards(); 
    round.callNumber(); 
    round.printCards(); 
    round.callNumber(); 
    round.printCards(); 
    round.callNumber(); 
    round.printCards(); 
    round.callNumber(); 
    round.printCards(); 
    round.callNumber(); 
    round.printCards(); 
    round.callNumber(); 
    round.printCards(); 
    round.callNumber(); 
    round.printCards(); 
    round.callNumber(); 
    round.printCards(); 
    std::cout << "After " << round.getNumSpacesCalled() << " called." << std::endl; 
    // Card myCard; 
    // myCard.Print(); 
    return 0; 
}