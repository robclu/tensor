// ----------------------------------------------------------------------------------------------------------
/// @file   tensortests.cpp
/// @brief  Test suites for the test_tensorlibrary using Bost.Unit.
// ----------------------------------------------------------------------------------------------------------

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE       TensorTests
#include <boost/test/unit_test.hpp>

#include "tensor/mapper.hpp"
#include "tensor/tensor.hpp"
#include "tensor/tensor_index.hpp"

#include <iostream>

BOOST_AUTO_TEST_SUITE( TensorIndex )

BOOST_AUTO_TEST_CASE( canUseATensorIndex ) 
{
    // Use index namespace, which hs indices like i,
    // j, ... etc already defined
    using namespace ftl::idx;
    
    BOOST_CHECK( i.value() == 0 );
    BOOST_CHECK( j.value() == 1 );
    
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------- INDEX MAPPER -------------------------------------------------

BOOST_AUTO_TEST_SUITE( IndexMapperSuite )

BOOST_AUTO_TEST_CASE( canMapIndexCorrectly )
{
    // Create a vector of dimensions
    std::vector<size_t> dimension_sizes = {3, 2, 4, 2};
    
    // Create a dimension mapper struct (the inteded use is as a functor, this is just for testing purposes)
    ftl::index_mapper mapper;
    
    // Determine the offset of elements in various dimensions
    size_t dim_1 = mapper(dimension_sizes, 2, 0, 0, 0);
    size_t dim_2 = mapper(dimension_sizes, 2, 1, 0, 0);
    size_t dim_3 = mapper(dimension_sizes, 1, 0, 2, 0);
    size_t dim_4 = mapper(dimension_sizes, 2, 1, 3, 1);
    
    BOOST_CHECK( dim_1 == 2  );
    BOOST_CHECK( dim_2 == 5  );
    BOOST_CHECK( dim_3 == 13 );
    BOOST_CHECK( dim_4 == 47 );
}

BOOST_AUTO_TEST_SUITE_END()
  
// -------------------------------------- TMP MAPPER OPERATIONS ---------------------------------------------
BOOST_AUTO_TEST_SUITE( MapperOperations )

BOOST_AUTO_TEST_CASE( canMapIndexToDimensionPositions )
{
    // Create a list of dimensions sizes which represent tesnor dimensions, so this 
    // is a rank 3 tensor with 3 rows, 2 columns and 2 pages
    using dim_sizes = nano::list<nano::int_t<3>, nano::int_t<2>, nano::int_t<2>>;
    
    // Now find the positions in each dimension of the index 10, which will be (2, 1, 1),
    // or 3nd row, 2nd column, 2nd page (O indexing is used)
    using position_list = ftl::mapper::index_to_dim_positions<nano::int_t<11>, dim_sizes>;
    
    // To make things easier, convert to a vector
    int first_index = nano::get<0, position_list>::value;
    int secnd_index = nano::get<1, position_list>::value;
    int third_index = nano::get<2, position_list>::value;
    
    BOOST_CHECK( first_index == 2 );
    BOOST_CHECK( secnd_index == 1 );
    BOOST_CHECK( third_index == 1 );
}

BOOST_AUTO_TEST_CASE( canMapIndextoIndexList )
{
    std::vector<size_t> dim_sizes{ {3, 2, 2} };
    
    auto index_list = ftl::mapper::index_to_index_list(11, dim_sizes);
    
    BOOST_CHECK( index_list[0] == 2 );
    BOOST_CHECK( index_list[1] == 1 );
    BOOST_CHECK( index_list[2] == 1 );
}

BOOST_AUTO_TEST_SUITE_END()
// --------------------------------------------- TENSOR -----------------------------------------------------   

BOOST_AUTO_TEST_SUITE( TensorSuite )
    
BOOST_AUTO_TEST_CASE( canCreateTensorWithDefaultConstructor ) 
{
    ftl::tensor<float, 3> test_tensor;                          // Rank 3 tensor
    BOOST_CHECK( test_tensor.size() == 0 );
}

BOOST_AUTO_TEST_CASE( canSpecifyTensorDimensionsWithList ) 
{
    ftl::tensor<float, 2> test_tensor = {4, 3};                 // Rank 2 tensor with 4 rows and 3 columns 
    BOOST_CHECK( test_tensor.size() == 12 );
}

BOOST_AUTO_TEST_CASE( canCreateTensorFromDimensionSizesAdnData )
{
    std::vector<size_t> dimension_sizes = {2, 3};
    std::vector<float>  data            = {1.f, 2.f,            // x0, x1, y0
                                           3.f, 4.f,            // x0, x1, y1
                                           5.f, 6.f};           // x0, x1, y2
    
    ftl::tensor<float, 2> test_tensor(dimension_sizes, data);
    const std::vector<float>& tensor_data = test_tensor.data();      
    
    BOOST_CHECK( tensor_data[0] == 1.f );
    BOOST_CHECK( tensor_data[1] == 2.f );
    BOOST_CHECK( tensor_data[2] == 3.f );
    BOOST_CHECK( tensor_data[3] == 4.f );
    BOOST_CHECK( tensor_data[4] == 5.f );
    BOOST_CHECK( tensor_data[5] == 6.f );
}

BOOST_AUTO_TEST_CASE( canGetRankOfTensor ) 
{
    ftl::tensor<float, 3> test_tensor = {1, 4, 4};
    
    BOOST_CHECK( test_tensor.rank() == 3 );
}

BOOST_AUTO_TEST_CASE( canGetTensorDimensions )
{
    ftl::tensor<int, 3> test_tensor = {2, 1, 3};
    
    std::vector<size_t> dims = test_tensor.dim_sizes();
    
    BOOST_CHECK( dims[0] == 2 );
    BOOST_CHECK( dims[1] == 1 );
    BOOST_CHECK( dims[2] == 3 );
}

BOOST_AUTO_TEST_CASE( canGetSizeOfTensor ) 
{
    ftl::tensor<double, 4> test_tensor = {2, 3, 2, 4};
    
    BOOST_CHECK( test_tensor.size() == 48 );
}

BOOST_AUTO_TEST_CASE( canGetSizeOfASpecificDimensionOfTensor ) 
{
    ftl::tensor<float, 3> test_tensor = {1, 2, 3};
    
    int dim_size_0 = test_tensor.size(0);
    int dim_size_2 = test_tensor.size(2);
    
    BOOST_CHECK( dim_size_0 == 1 );
    BOOST_CHECK( dim_size_2 == 3 );
}

BOOST_AUTO_TEST_CASE( canSetElementOfTensor ) 
{
    ftl::tensor<int, 3> test_tensor = {3, 3, 3};
    
    // Set 2nd element 
    test_tensor(1, 0, 0) = 4;
    
    // Get data 
    const std::vector<int>& tensor_data = test_tensor.data();
    
    BOOST_CHECK( tensor_data[1] == 4 );
}

BOOST_AUTO_TEST_CASE( canGetElementOfTensor ) 
{
    ftl::tensor<int, 3> test_tensor = {3, 3, 3};
    
    // Set 2nd element 
    test_tensor(1, 0, 0) = 12;
    
    // Get 2nd element now
    int element = test_tensor(1, 0, 0);
    
    BOOST_CHECK( element == 12 );
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------- TENSOR OPERATIONS --------------------------------------------------------

BOOST_AUTO_TEST_SUITE( TensorOperations )

BOOST_AUTO_TEST_CASE( canInitializeATensor )
{
    ftl::tensor<int, 3> tensor = {2, 2, 2};
    
    // Initialize all values to 1
    ftl::initialize(tensor, 1, 1);
    
    BOOST_CHECK( tensor(0, 0, 0) == 1 );
}

BOOST_AUTO_TEST_CASE( dimensionsAreCorrectWhenAddingTensors ) 
{
    ftl::tensor<float, 3> tensor_1     = {1, 2, 3};
    ftl::tensor<float, 3> tensor_2     = {1, 2, 3};
    ftl::tensor<float, 3> tensor_3     = {1, 2, 3};
    
    ftl::tensor<float, 3>  added_tensor = tensor_1 + tensor_2 + tensor_3;
   
    BOOST_CHECK( added_tensor.size() == tensor_1.size() ); 
    BOOST_CHECK( added_tensor.size() == tensor_2.size() ); 
    BOOST_CHECK( added_tensor.size() == tensor_3.size() ); 
}

BOOST_AUTO_TEST_CASE( dimensionsAreCorrectWhenSubtractingTensors ) 
{
    ftl::tensor<float, 3> tensor_1     = {1, 2, 3};
    ftl::tensor<float, 3> tensor_2     = {1, 2, 3};
    ftl::tensor<float, 3> tensor_3     = {1, 2, 3};
    
    ftl::tensor<float, 3> subtracted_tensor   = tensor_1 - tensor_2 - tensor_3;
    
    BOOST_CHECK( subtracted_tensor.size() == tensor_1.size() ); 
    BOOST_CHECK( subtracted_tensor.size() == tensor_2.size() ); 
    BOOST_CHECK( subtracted_tensor.size() == tensor_3.size() ); 
}

BOOST_AUTO_TEST_CASE( canMultiplyTensors )
{
    // To use the index variables
    using namespace ftl::idx;    
    
    ftl::tensor<int, 2> test_tensor_1 = {3, 2};
    ftl::tensor<int, 2> test_tensor_2 = {2, 3};
    
    // Get a tensor_multiplier from the () operator
    auto t_multiplier = test_tensor_1(i, j) * test_tensor_2(j, k);
    
    std::vector<size_t> multiplier_dim_sizes = t_multiplier.dim_sizes();
    
    for (auto& size : multiplier_dim_sizes)
        std::cout << "Size : " << size << "\n";
}

BOOST_AUTO_TEST_CASE( canGetRankOfTensorAfterMultiplication )
{
    using namespace ftl::idx;
   
    std::vector<size_t> ds1     = {3, 2};
    std::vector<size_t> ds2     = {2, 3};
    std::vector<int>    data1   = { 1, 2, 3, 4 , 5 , 6  };
    std::vector<int>    data2   = { 7, 8, 9, 10, 11, 12 };
    
    ftl::tensor<int, 2> tensor_1(ds1, data1);
    ftl::tensor<int, 2> tensor_2(ds2, data2);

    // Perform tensor multiplication (in this example this is exactly matrix multiplication 
    // of the tesnor as the second dimension of the first tensor and the first dimension of 
    // the second tensor are reduced) the result is a rank 2 tensor with dimensions of 3x3
    auto result = tensor_1(i, j) * tensor_2(j, k);
    
    result.calculate_value(1);
    
    // COME back to this
    // constexpr size_t size = result.size();
    
    // BOOST_CHECK( size == 9 );
}

// Need To check that the values are actually correct
BOOST_AUTO_TEST_SUITE_END()
