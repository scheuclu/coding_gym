#include <iostream>
#include <vector>
#include <numeric>
#include <execution>

// Driver code 
int main() 
{ 
    int numbers[10]; 
    // Initailising starting value as 100 
    int st = 100; 
  
    std::iota(std::begin(numbers), std::end(numbers), st); 
  
    std::cout << "Elements are :"; 
    for (auto i : numbers) 
        std::cout << ' ' << i; 
    std::cout << '\n'; 
  
    return 0; 
} 