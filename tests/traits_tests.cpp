// ----------------------------------------------------------------------------------------------------------
/// @file   traits_tests.cpp
/// @brief  Test suite for traits tests 
// ----------------------------------------------------------------------------------------------------------

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
    #define BOOST_TEST_MODULE TraitsTests
#endif
#include <boost/test/unit_test.hpp>

#include "../tensor/tensor_traits.hpp"

BOOST_AUTO_TEST_SUITE( TensorTraitsSuite)

BOOST_AUTO_TEST_CASE( canDetermineStaticContainerFromTraits )
{
    // Define traits for tensor 
    //  : int data type
    //  : cpu implementation
    //  : dimension sizes of 2 and 3
    using traits = ftl::TensorTraits<int, ftl::CPU, 2, 3>;
    
    // Create a container using the traits class
    traits::container_type A;
    
    BOOST_CHECK( A.size() == 6 );
}

BOOST_AUTO_TEST_SUITE_END()
