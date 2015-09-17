#include <array>
#include <iostream>

using std::array;
using std::cout;

constexpr size_t D1 = 200;
constexpr size_t D2 = 3000;

int main(int argc, char** argv)
{
    array<size_t, D1 * D2> container;   
    size_t offset = 0;    
   
    for (size_t i = 0; i < D1; ++i) 
        for (size_t j = 0; j < D2; ++j) 
            offset = container[i * D1 + j];    
    
    std::cout << offset;
}
