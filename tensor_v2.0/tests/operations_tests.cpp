// ----------------------------------------------------------------------------------------------------------
/// @file   operations_tests.cpp
/// @brief  Test suite for tensor operationstests 
// ----------------------------------------------------------------------------------------------------------

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
    #define BOOST_TEST_MODULE Operations
#endif
#include <boost/test/unit_test.hpp>

#include "../tensor.hpp"
#include "../tensor_operations.hpp"

#include <iostream>

BOOST_AUTO_TEST_SUITE( OperationsSuite )
    
BOOST_AUTO_TEST_CASE( canAdd2StaticTensors )
{
    ftl::Tensor<int, ftl::CPU, 2, 2> A{ 1, 2, 3, 4 };
    ftl::Tensor<int, ftl::CPU, 2, 2> B{ 1, 2, 3, 4 };
    
    auto C = A + B;
    ftl::Tensor<int, ftl::CPU, 2, 2> D = A + B;
    
    BOOST_CHECK( C[0] == 2 );
    BOOST_CHECK( D[0] == 2 );
    BOOST_CHECK( C[1] == 4 );
    BOOST_CHECK( D[1] == 4 );
    BOOST_CHECK( C[2] == 6 );
    BOOST_CHECK( D[2] == 6 );
    BOOST_CHECK( C[3] == 8 );
    BOOST_CHECK( D[3] == 8 );
}

BOOST_AUTO_TEST_CASE( canAdd2DynamicTensors )
{
    // Create 2 dynamic tensors of rank 2 
    // with dimension size of 2x2
    ftl::Tensor<int, ftl::CPU> A{ 2, 2 };
    ftl::Tensor<int, ftl::CPU> B{ 2, 2 };
    
    // Intialize A to have values of 1, and B to have values of 2
    A.initialize(1, 1);
    B.initialize(2, 2);
    
    auto C = A + B;
    ftl::Tensor<int, ftl::CPU> D = A + B;
    
    BOOST_CHECK( C[0] == 3 );
    BOOST_CHECK( D[0] == 3 );
    BOOST_CHECK( C[1] == 3 );
    BOOST_CHECK( D[1] == 3 );
    BOOST_CHECK( C[2] == 3 );
    BOOST_CHECK( D[2] == 3 );
    BOOST_CHECK( C[3] == 3 );
    BOOST_CHECK( D[3] == 3 ); 
}

BOOST_AUTO_TEST_CASE( canAddAStaticAndDynamicTensorToGetAStaticTensor )
{
    ftl::Tensor<int, ftl::CPU, 2, 2> A{ 1, 2, 3, 4 };
    ftl::Tensor<int, ftl::CPU> B{ 2, 2 };
    
    // Initialize B with values of 10
    B.initialize(10, 10);

    // Addition takes the traits of the first tensor in the addition (A)
    // So C and D are static tensors since A is a static tensor
    auto C = A + B;
    ftl::Tensor<int, ftl::CPU, 2, 2> D = A + B;
    
    BOOST_CHECK( C[0] == 11 );
    BOOST_CHECK( D[0] == 11 );
    BOOST_CHECK( C[1] == 12 );
    BOOST_CHECK( D[1] == 12 );
    BOOST_CHECK( C[2] == 13 );
    BOOST_CHECK( D[2] == 13 );
    BOOST_CHECK( C[3] == 14 );
    BOOST_CHECK( D[3] == 14 ); 
    
}

BOOST_AUTO_TEST_CASE( canAddADynamicAndStaticTensorToGetADynamicTensor )
{
    ftl::Tensor<int, ftl::CPU> A{ 2, 2 };
    ftl::Tensor<int, ftl::CPU, 2, 2> B{ 1, 2, 3, 4 };
    
    // Initialize A with values of 10
    A.initialize(10, 10);

    // Addition takes the traits of the first tensor in the addition (A)
    // So C and D are dynamic tensors since A is a dynamic tensor
    auto C = A + B;
    ftl::Tensor<int, ftl::CPU> D = A + B;
    
    BOOST_CHECK( C[0] == 11 );
    BOOST_CHECK( D[0] == 11 );
    BOOST_CHECK( C[1] == 12 );
    BOOST_CHECK( D[1] == 12 );
    BOOST_CHECK( C[2] == 13 );
    BOOST_CHECK( D[2] == 13 );
    BOOST_CHECK( C[3] == 14 );
    BOOST_CHECK( D[3] == 14 ); 
}

BOOST_AUTO_TEST_SUITE_END()
