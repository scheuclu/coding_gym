#include <vector>
#include <sstream>
#include <unordered_map>

//forward declaration
struct GameStateHasher;

class GameState{
    public:
        std::vector<int> piles;
        std::vector<bool> zeromoves;
        bool isJohn;
        // declare global variable
        static std::unordered_map<GameState, bool, GameStateHasher> gs_tracker;
        bool operator==(const GameState  &) const;
        static std::vector<int> getPossibleNormalMoves(const std::vector<int> &piles);
        static std::vector<int> getPossibleZeroMoves(const std::vector<int> &piles, const std::vector<bool> &zeromove);

};

bool GameState::operator==(const GameState  &f) const {
    return (
    (piles == f.piles) &&
    (zeromoves==f.zeromoves) &&
    (isJohn == f.isJohn));
}

//return indices of non-zero piles
std::vector<int> GameState::getPossibleNormalMoves(const std::vector<int> &piles){
    std::vector<int> result;
    for (int i=0; i<piles.size(); ++i){
        if(piles[i]!=0){
            result.push_back(i);
        }
    }
    return result;
}

//return indices of piles with no zero-move yet
//No need to try zero moves unless there's 2 or less ont he pile
std::vector<int> GameState::getPossibleZeroMoves(const std::vector<int> &piles, const std::vector<bool> &zeromove){
    std::vector<int> result;
    for (int i=0; i<zeromove.size(); ++i){
        if(zeromove[i]==false && piles[i]<3){
            result.push_back(i);
        }
    }
    return result;
}

// Custom hash function for type GameState
struct GameStateHasher {
    std::hash<std::string> hasher;//defined by unordered map
    int operator()(const GameState &gs) const {
        std::stringstream ss;
        for (auto i: gs.piles){
            ss << i;
        }
        ss<<"-";
        for (auto i: gs.zeromoves){
            ss << i;
        }
        //std::cout<<"STRING: "<<ss.str()<<std::endl;
        return hasher(ss.str());
    }
};



// One can simple reduce each pile by multiples of 2
GameState reduceMagic(GameState gs){
   std::vector<int>::iterator it;
    for(it=gs.piles.begin(); it!=gs.piles.end(); it++){
        while (*it>5){
            *it-=2;
        }
    }

    return gs;

};