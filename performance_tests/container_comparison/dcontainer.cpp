#include "../../tensor/container_mapper.hpp"
#include <vector>

constexpr size_t D1 = 200;
constexpr size_t D2 = 3000;
constexpr size_t D3 = 7;
constexpr size_t D4 = 2;
constexpr size_t D5 = 2;
constexpr size_t D6 = 12;

int main(int argc, char** argv)
{
    
    std::vector<size_t> dim_sizes{ D1, D2, D3, D4, D5, D6 };
    size_t offset = 0;
    
    for (size_t i = 0; i < D1; ++i) 
        for (size_t j = 0; j < D2; ++j) 
            offset = ftl::dynamic_mapper::indices_to_index(dim_sizes, i, j, 2, 0, 1, 8);    
            
    std::cout << offset;
}
