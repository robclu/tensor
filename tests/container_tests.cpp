// ----------------------------------------------------------------------------------------------------------
/// @file   container_tests.cpp
/// @brief  Test suites for container tests 
// ----------------------------------------------------------------------------------------------------------

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
    #define BOOST_TEST_MODULE ContainerTests
#endif
#include <boost/test/unit_test.hpp>

#ifndef FTL_TENSOR_CONTAINER_HPP
    #include "../tensor/tensor_container.hpp"
#endif

BOOST_AUTO_TEST_SUITE( TensorContainerSuite)

// TODO: Add tests that conver entire container functionality
    
BOOST_AUTO_TEST_CASE( canCreateStaticContainer )
{
    // Create a container specifying the dimension sizes
    ftl::TensorContainer<int, 2, 3> A;
    
    BOOST_CHECK( A.size() == 6 );
}

BOOST_AUTO_TEST_CASE( canCreateDynamicContainer )
{
    // Create a container without specifying the dimensions
    ftl::TensorContainer<int> A;
    
    BOOST_CHECK( A.size() == 0 );
}

BOOST_AUTO_TEST_SUITE_END()
