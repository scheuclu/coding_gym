// https://www.hackerrank.com/challenges/vector-sort/problem

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

// This is used as replacement for the cin stream on hackerrank
std::ifstream fin("input/test_case_0.txt", std::ifstream::in);

//using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int num, a;
    std::vector<int> nums;

    fin >> num;
    //std::cout<<"num "<<num<<std::endl;
    while (fin>>a){
        //std::cout<<"a "<<a<<std::endl;
        nums.push_back(a);
    };


    //Sort the vector
    std::sort(nums.begin(), nums.end());  

    for (auto i: nums){
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;

    return 0;
} 