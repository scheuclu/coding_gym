
#include <iostream>
#include <vector>
#include <algorithm> // transform
#include <cmath> //pow
#include <numeric> //accumulate

//using namespace std;


//A function that outputs all elements of a vector to stdout

template <class T>
void printVector(std::vector<T> v, char sep=','){
    typename std::vector<T>::iterator it; //TODO(scheuclu) Research when 'typename' is needed.
    for(it=v.begin(); it!=v.end(); it++){
        std::cout<<*it<<sep;
    }
    std::cout<<std::endl;
}

int main (){


   // a -----------------------------------
   std::vector<int> a;
   a.push_back(1);
   a.push_back(2);
   a.push_back(3);
   a.push_back(4);
   std::cout<<"This is vector a before pop operations:"<<std::endl;
   printVector(a);

   std::cout<<std::endl;

   //Now pop from the vector until empty
   while (!a.empty()){
       std::cout<<"I popped "<<a.back()<<std::endl;
       a.pop_back();
   }
   std::cout<<std::endl;
   std::cout<<"This is vector a after pop operations:"<<std::endl;
   printVector(a);


   // b -----------------------------------
   std::vector<int> numbers={1, 2, 3, 4};
   std::vector<int> exponent={0, 1, 2, 3};

   // version 1 - basic
   std::vector<int>::iterator itn=numbers.begin();
   std::vector<int>::iterator ite=exponent.begin();
   int result = 0;
   while(itn!=numbers.end() & ite!=exponent.end()){
      result+=*itn*std::pow(10, *ite);
      itn++;
      ite++;
   }
   std::cout<<"v1: The result it "<<result<<std::endl;


   // version 2 - using transform
   std::vector<int> results;
   std::transform(numbers.begin(), numbers.end(), exponent.begin(), std::back_inserter(results), 
      [](int i, int j){return i*pow(10,j);});
   std::cout<<"v2: The results are:"<<std::endl;
   printVector(results);
   int sum = std::accumulate(results.begin(), results.end(), 0);
   std::cout<<"v2: The number is "<<sum<<std::endl;




}