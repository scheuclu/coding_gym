#include <vector>
#include <sstream>
#include <unordered_map>

class GameState{
    public:
        std::vector<int> piles;
        std::vector<bool> zeromoves;
        bool isJohn;
        bool operator==(const GameState  &) const;
        static std::vector<int> getPossibleNormalMoves(std::vector<int> piles);
        static std::vector<int> getPossibleZeroMoves(std::vector<bool> zeromove);
};
bool GameState::operator==(const GameState  &f) const {
    return (
    (piles == f.piles) &&
    (zeromoves==f.zeromoves) &&
    (isJohn == f.isJohn));
}

//return indices of non-zero piles
std::vector<int> GameState::getPossibleNormalMoves(std::vector<int> piles){
    std::vector<int> result;
    for (int i=0; i<piles.size(); ++i){
        if(piles[i]!=0){
            result.push_back(i);
        }
    }
    return result;
}

//return indices of piles with no zero-move yet
std::vector<int> GameState::getPossibleZeroMoves(std::vector<bool> zeromove){
    std::vector<int> result;
    for (int i=0; i<zeromove.size(); ++i){
        if(zeromove[i]==false){
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