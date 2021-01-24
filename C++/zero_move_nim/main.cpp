// https://www.hackerrank.com/challenges/zero-move-nim/problem

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <functional>
#include <unordered_map>
#include <string>
#include <sstream>


struct GameState{
    std::vector<int> piles;
    std::vector<bool> zeromoves;
    bool isJohn;
    bool operator==(const GameState  &) const;
};
bool GameState::operator==(const GameState  &f) const {
    return (
    (piles == f.piles) &&
    (zeromoves==f.zeromoves) &&
    (isJohn == f.isJohn));
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
// declare global variable
std::unordered_map<GameState, bool, GameStateHasher> gs_tracker;

// This is used as replacement for the cin stream on hackerrank
std::ifstream fin("input/test_case_1.txt", std::ifstream::in);


//return indices of non-zero piles
std::vector<int> getPossibleNormalMoves(std::vector<int> piles){
    std::vector<int> result;
    for (int i=0; i<piles.size(); ++i){
        if(piles[i]!=0){
            result.push_back(i);
        }
    }
    return result;
}

//return indices of piles with no zero-move yet
std::vector<int> getPossibleZeroMoves(std::vector<bool> zeromove){
    std::vector<int> result;
    for (int i=0; i<zeromove.size(); ++i){
        if(zeromove[i]==false){
            result.push_back(i);
        }
    }
    return result;
}


bool johnWins(GameState gs){
   
   // Chech the memo-map. Maybe we have already seen that gamestate
   if (gs_tracker.find(gs)!=gs_tracker.end()){
       //std::cout<<"MEMO WORKS"<<std::endl;
       return gs_tracker[gs];
   }

   //base case of the player winning
   auto pos_norm_moves=getPossibleNormalMoves(gs.piles);
   auto pos_zero_moves=getPossibleZeroMoves(gs.zeromoves);

   // Base case: no zero-moves and only one pile left with size 1
   if(pos_zero_moves.size()==0 && pos_norm_moves.size()==1 && gs.piles[pos_norm_moves[0]]==1){
       // If it's John's turn in this situation he wins, otherwise he loses
       gs_tracker[gs]=gs.isJohn;
       return gs.isJohn;
   }

   // Do all possible moves and recurse. Switch the player flag.
   std::vector<bool> results;
   for (auto i: pos_norm_moves){
       GameState new_gs(gs);
       new_gs.piles[i]--;
       new_gs.isJohn=!new_gs.isJohn;
       results.push_back(johnWins(new_gs));
   }
   for (auto i: pos_zero_moves){
       GameState new_gs(gs);
       new_gs.zeromoves[i]=true;
       new_gs.isJohn=!new_gs.isJohn;
       results.push_back(johnWins(new_gs));
   }

    // If it's Johns turn, then he wins, so long as any of the moves returns true
    bool result;
    if(gs.isJohn){
        result = std::find(results.begin(), results.end(), true)!=results.end();
    } else {
        result = std::find(results.begin(), results.end(), false)==results.end();
    }
    gs_tracker[gs]=result;
    return result;

}

char zeroMoveNim(std::vector<int> piles) {
    /*
     * Write your code here.
     */

    char result;
    
    // Inititalize the vector, thats keeping track of zero moves
    std::vector<bool> zeromoves(piles.size());
    GameState gs{piles, zeromoves, true};
    bool win = johnWins(gs);
    if (win){
        return 'W';
    }
    return 'L';
}




int main(){
   std::string word;
   int N, L, num;

   fin >> N;
   std::cout<<"N: "<<N<<std::endl;
   

   // Loop over number of games
   for(int i=0; i<N; ++i){
      std::vector<int> vec;
      fin >> L;
      std::cout<<"L: "<<L<<std::endl;
      
      // Read int the config of game i
      for( int j=0; j<L; ++j ) {
        fin>>num;
        std::cout<<num<<" ";
        vec.push_back(num);
      }
      std::cout<<std::endl;
      
      char result = zeroMoveNim(vec);
      std::cout<<"Result: "<<result<<std::endl;
   }

   

}