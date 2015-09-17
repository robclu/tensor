#include "../../tensor/container_mapper.hpp"
#include "../../tensor/static_tensor.hpp"
#include "../../tensor/tensor.h"

constexpr size_t D1 = 200;
constexpr size_t D2 = 3000;
constexpr size_t D3 = 7;
constexpr size_t D4 = 20;
constexpr size_t D5 = 2;
constexpr size_t D6 = 12;

int main(int argc, char** argv)
{
    // Define sype for static tensor
    using static_type   = ftl::stensor<int, D1, D2, D3, D4, D5, D6>;            // Static tensor type
    using dim_sizes     = static_type::data_container::dimension_sizes;         // dim sizes of static tensor
    
    size_t offset = 0;    
   
    for (size_t i = 0; i < D1; ++i) 
        for (size_t j = 0; j < D2; ++j) 
            offset = ftl::static_mapper::indices_to_index<dim_sizes>(i, j, 2, 0, 1, 8);    
    
    std::cout << offset;
}
