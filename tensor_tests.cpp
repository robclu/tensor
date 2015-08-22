// ----------------------------------------------------------------------------------------------------------
/// @file   tensortests.cpp
/// @brief  Test suites for the test_tensorlibrary using Bost.Unit.
// ----------------------------------------------------------------------------------------------------------

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE       TensorTests
#include <boost/test/unit_test.hpp>

#include "tensor/tensor.hpp"

#include <iostream>

BOOST_AUTO_TEST_SUITE( TensorExpressionsTestSuite )

BOOST_AUTO_TEST_SUITE_END()
 
// --------------------------------------- TENSOR TESTS -----------------------------------------------------   

BOOST_AUTO_TEST_SUITE( TensorTestSuite )
    
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



BOOST_AUTO_TEST_SUITE_END()
