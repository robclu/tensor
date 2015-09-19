// ----------------------------------------------------------------------------------------------------------
/// @file   tensor_tests.cpp
/// @brief  Test suite for tensor tests 
// ----------------------------------------------------------------------------------------------------------

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
    #define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>

#include "../tensor_interface.hpp"

BOOST_AUTO_TEST_SUITE( TensorSuite)
    
BOOST_AUTO_TEST_CASE( canCreateDynamicTensor )
{
    // Define traits for tensor 
    //  : int data type
    //  : cpu implementation
    //  : dimension sizes of 2 and 3
    using dynamic_tensor = ftl::Tensor<int, ftl::CPU>;
    
    // Create a container using the traits class
    //traits::container_type A;
    
    //BOOST_CHECK( A.size() == 6 );
}

BOOST_AUTO_TEST_SUITE_END()
