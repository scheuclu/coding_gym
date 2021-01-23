// https://www.hackerrank.com/challenges/zero-move-nim/problem

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <functional>
#include <unordered_map>



// struct VectorHasher {
//     int operator()(const std::vector<int> &V) const {
//         int hash = V.size();
//         for(auto &i : V) {
//             hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
//         }
//         return hash;
//     }
// };

// This is used as replacement for the cin stream on hackerrank
std::ifstream fin("input/test_case_0.txt", std::ifstream::in);


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


bool johnWins(std::vector<int> piles, std::vector<bool> zeromove, bool isJohn){
   //base case of the player winning
   auto pos_norm_moves=getPossibleNormalMoves(piles);
   auto pos_zero_moves=getPossibleZeroMoves(zeromove);

   // Base case: no zero-moves and only one pile left with size 1
   if(pos_zero_moves.size()==0 && pos_norm_moves.size()==1 && piles[pos_norm_moves[0]]==1){
       // If it's John's turn in this situation he wins, otherwise he loses
       return isJohn;
   }

   // Do all possible moves and recurse. Switch the player flag.
   std::vector<bool> results;
   for (auto i: pos_norm_moves){
       std::vector<int> new_piles(piles);
       new_piles[i]--;
       results.push_back(johnWins(new_piles, zeromove, !isJohn));
   }
   for (auto i: pos_zero_moves){
       std::vector<bool> new_zeromove(zeromove);
       new_zeromove[i]=true;
       results.push_back(johnWins(piles, new_zeromove, !isJohn));
   }

    // If it's Johns turn, then he wins, so long as any of the moves returns true
    if(isJohn){
        return std::find(results.begin(), results.end(), true)!=results.end();
    } else {
        // If it's Kates turn, then he wins, so long as there is no turn here that makes Kate win
        // Remember, both player are palying optimally.
        return std::find(results.begin(), results.end(), false)==results.end();
    }


}

char zeroMoveNim(std::vector<int> piles) {
    /*
     * Write your code here.
     */

    char result;
    
    // Inititalize the vector, thats keeping track of zero moves
    std::vector<bool> zeromove(piles.size());
    bool win = johnWins(piles, zeromove, true);
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