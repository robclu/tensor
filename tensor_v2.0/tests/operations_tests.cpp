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

BOOST_AUTO_TEST_SUITE( OperationsSuite )
    
BOOST_AUTO_TEST_CASE( canAdd2StaticTensors )
{
    ftl::Tensor<int, ftl::CPU, 2, 2> A{ 1, 2, 3, 4 };
    ftl::Tensor<int, ftl::CPU, 2, 2> B{ 1, 2, 3, 4 };
    
    auto C = A + B;
    ftl::Tensor<int, ftl::CPU, 2, 2> D = A + B;
        
    BOOST_CHECK( C[0] == 2 );
    BOOST_CHECK( D[0] == 2 );
//    BOOST_CHECK( C[1] == 4 );
//    BOOST_CHECK( C[2] == 6 );
//    BOOST_CHECK( C[3] == 8 );
}

BOOST_AUTO_TEST_SUITE_END()
