// https://www.hackerrank.com/challenges/simple-array-sum/problem

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

// This is used as replacement for the cin stream on hackerrank
std::ifstream fin("input/test_case_0.txt", std::ifstream::in);


int main(){

    if (!fin.is_open()){
        std::cout<<"Cannot open file!"<<std::endl;
        return 0;
    }

    int N;
    fin >> N;
    std::cout<<N<<std::endl;

    // Read the next line and split by whitespace
    std::string line, word;
    std::vector<int> nums;
    

    for (int i=0; i<N; ++i){
        fin >> word;
        nums.push_back(std::stoi(word));
    }

    std::cout<<"nums:"<<std::endl;
    std::vector<int>::iterator it;
    for (it=nums.begin(); it!=nums.end(); it++){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"sum: "<<std::accumulate(nums.begin(), nums.end(), 0)<<std::endl;
}
