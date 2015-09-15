#include "../tensor/container_mapper.hpp"
#include "../tensor/static_tensor.hpp"
#include "../tensor/tensor.h"

int main(int argc, char** argv)
{
    // Define sype for static tensor
    using static_type   = ftl::stensor<int, 2, 2, 2, 3>;                    // Static tensor type
    using dim_sizes     = static_type::data_container::dimension_sizes;     // dim sizes of static tensor
    
    // Create a static tensor
    static_type stensor;
    
    size_t offset = ftl::static_mapper::indices_to_index<dim_sizes>(0, 1, 1, 0);    
    
    std::cout << offset > 0 ? 0 : 1;
}
