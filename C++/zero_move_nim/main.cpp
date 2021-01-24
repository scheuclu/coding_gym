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
#include "games_state.h"
#include <set>


// This is used as replacement for the cin stream on hackerrank
std::ifstream fin("input/test_case_3.txt", std::ifstream::in);


bool johnWins(GameState gs){

   // Chech the memo-map. Maybe we have already seen that gamestate
   if (GameState::gs_tracker.find(gs)!=GameState::gs_tracker.end()){
       return GameState::gs_tracker[gs];
   }

   //base case of the player winning
   auto pos_norm_moves=GameState::getPossibleNormalMoves(gs.piles);
   auto pos_zero_moves=GameState::getPossibleZeroMoves(gs.piles, gs.zeromoves);

   // Base case: no zero-moves and only one pile left with size 1
   if(pos_zero_moves.size()==0 && pos_norm_moves.size()==1 && gs.piles[pos_norm_moves[0]]==1){
       // If it's John's turn in this situation he wins, otherwise he loses
       GameState::gs_tracker[gs]=gs.isJohn;
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


    bool result;
    if(gs.isJohn){
        // If it's Johns turn, then he wins, so long as any of the moves returns true
         result = std::find(results.begin(), results.end(), true)!=results.end();
    } else {
        // If it's Kates turn, then he wins, so long as there is no turn here that makes Kate win
        // Remember, both player are palying optimally.
        result = std::find(results.begin(), results.end(), false)==results.end();
    }
    GameState::gs_tracker[gs]=result;
    return result;

}

char zeroMoveNim(std::vector<int> piles) {

    // Inititalize the vector, thats keeping track of zero moves
    std::vector<bool> zeromoves(piles.size());
    GameState gs{piles, zeromoves, true};
    gs = reduceMagic(gs);
    for(auto i: gs.piles){
        std::cout<<i<<"-";
    }; std::cout<<std::endl;
    char result = johnWins(gs) ? 'W' : 'L';
    return result;
}

// static member variable need to be initialized at the global namespace
std::unordered_map<GameState, bool, GameStateHasher> GameState::gs_tracker{};
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

// How to fix this
// 1. Do all possible zero move combinations right away 
// 2. Then play regular zero nims
// 3. Use an std::set to store the piles. That way the the order of piles won't matter when hashed.