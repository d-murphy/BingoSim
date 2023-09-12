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
        bool isWinner(){
            // check verticals
            for(int i = 0; i<5; i++){
                bool allTrue = true; 
                for(int j=0; j<5; j++){
                    if(!markers[i][j]) {
                        allTrue = false; 
                        break; 
                    }
                }
                if(allTrue) return true; 
            }
            // check horizontals
            for(int j=0; j<5; j++){
                bool allTrue = true; 
                for(int i = 0; i<5; i++){
                    if(!markers[i][j]) {
                        allTrue = false; 
                        break; 
                    }
                }
                if(allTrue) return true; 
            }
            // check diagonal
            if(markers[0][0] && markers[1][1] && markers[2][2] && markers[3][3] && markers[4][4]) return true; 
            if(markers[0][4] && markers[1][3] && markers[2][2] && markers[3][1] && markers[4][0]) return true; 
            return false; 
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
            spacesCalled++; 
            int numCalled = numbersCalled.back(); 
//            std::cout << "The next number is: " << numCalled << "(" << spacesCalled << ")" << std::endl; 
            for(auto & card: cards){
                card.markSpace(numCalled); 
            }; 
            numbersCalled.pop_back(); 
        }
        bool isThereAWinner(){
            bool aWinner = false; 
            for(auto card: cards){
                if(card.isWinner()) aWinner = true; 
            }
            return aWinner; 
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

class Simulation {
    public: 
        Simulation(int maxNumCardsParam = 5){
            maxNumCards = maxNumCardsParam; 
        }
        void runSimmy(){
            for(int numCards = 1; numCards <= maxNumCards; numCards++){
                std::vector<int> simulationResults; 
                for(int i=0; i<1000; i++){
                    Round round(numCards); 
                    int aWinner = false; 
                    while(!aWinner){
                        round.callNumber(); 
                        aWinner = round.isThereAWinner(); 
                    };
                    simulationResults.push_back(round.getNumSpacesCalled());  
                }
                std::cout << "Finished 1000 simulations for " << numCards << " card" << (numCards > 1 ? "s" : "") << std::endl; 
                results.push_back(simulationResults); 
            }
            std::cout << "\n\nFinished Simulations\n\n" << std::endl; 
        }
        void checkMax(){
            std::cout << "maxNumCards: " << maxNumCards << std::endl; 
        }
        void printResults(){
            for(auto numCardGroup: results){
                for(auto spacesCalled: numCardGroup){
                    std::cout << spacesCalled << " "; 
                }
                std::cout << "\nend of numCardGroup\n" << std::endl; 
            }
        }
        void printPercentiles(){
            int numberOfCards = 1; 
            for(auto numCardGroup: results){
                std::string plural = numberOfCards > 1 ? "s" : ""; 
                std::cout << "Results for " << numberOfCards << " card" << plural << " ------> "; 
                sort(numCardGroup.begin(), numCardGroup.end());
                std::cout << 
                    "\t\tMin: " << numCardGroup[0] << 
                    "\t\tQ1: " << numCardGroup[249] << 
                    "\t\tMedian: " << numCardGroup[499] << 
                    "\t\tQ3: " << numCardGroup[749] << 
                    "\t\tMax: " << numCardGroup[999] << std::endl; 
                numberOfCards++; 
            }

        }
    private: 
        std::vector<std::vector<int>> results; 
        int maxNumCards; 
}; 



int main(){
    std::cout 
        << "\n\n\n\n-----BINGO SIMULATION ANALYSIS------\n\n\n\n" 
        << "Finding how soon games finish as more cards are added.\n\n"
        << "Running 1000 simulations for different numbers of cards up to 30.\n\n"
        << std::endl; 
    Simulation simulation(30); 
    simulation.runSimmy(); 
    simulation.printPercentiles(); 
    return 0; 
}