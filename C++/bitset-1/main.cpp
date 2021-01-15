// https://www.hackerrank.com/challenges/bitset-1/problem

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

// This is used as replacement for the cin stream on hackerrank
std::ifstream fin("input/test_case_2.txt", std::ifstream::in);

// This is used for simple integer-range for loops
#define FOR(start, stop) for (long _i = start; _i < stop; _i++)

int main() {
    long N, S, P, Q, MOD=1, a;
    fin>>N;
    fin>>S;
    fin>>P;
    fin>>Q;

    MOD=(MOD<<31);
    //std::cout<<"MOD "<<MOD<<std::endl;

    std::unordered_set<int> seen;


    a=S%MOD;
    seen.insert(a);
    //std::cout<<a<<std::endl;

    FOR(1, N){
       a = (a*P+Q)%MOD;

       //std::cout<<a<<std::endl;
       if(seen.find(a)!=seen.end()){
           break;
       }
       seen.insert(a);
    }

    std::cout<<seen.size()<<std::endl;
    
    return 0;
}