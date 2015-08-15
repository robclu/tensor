// ----------------------------------------------------------------------------------------------------------
/// @file   ftl_tests.cpp
/// @brief  Test suites for the ftl library using Bost.Unit.
// ----------------------------------------------------------------------------------------------------------

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE       FtlTests
#include <boost/test/unit_test.hpp>

#include "meta/numeric_types.hpp"
#include "meta/functions.hpp"
#include "meta/containers.hpp"

#include <iostream>

BOOST_AUTO_TEST_SUITE( NumericTypeTestSuite )
    
BOOST_AUTO_TEST_CASE( canCreateStaticFtlIntType )
{
    ftl::int_t<2> static_int;
    
    BOOST_CHECK( static_int.runtime_value() == 2 );
}

BOOST_AUTO_TEST_CASE( canCreateStaticFtlSizeType )
{
    ftl::size_t<0> static_size_type;
    
    BOOST_CHECK( static_size_type.runtime_value() == 0 );
}

BOOST_AUTO_TEST_CASE( canUseDefinedDimensionTypes )
{
    using namespace ftl::dim;                    // To access dimension variables
    
    BOOST_CHECK( i.runtime_value() == 0 );
    BOOST_CHECK( j.runtime_value() == 1 );
}

BOOST_AUTO_TEST_SUITE_END()
    
BOOST_AUTO_TEST_SUITE( ListTestSuite )
    
BOOST_AUTO_TEST_CASE( canCreateAList )
{
    using test_list = ftl::list<ftl::int_t<3>, ftl::size_t<9>>;
    using type_one  = ftl::get<0, test_list>;   // Should be ftl::int_t<3>   
    using type_two  = ftl::get<1, test_list>;   // Should be ftl::size_t<9>
    
    // Decalre elements of the types to get their runtime values
    type_one elem_zero;         
    type_two elem_one;
    
    BOOST_CHECK( elem_zero.runtime_value() == 3 );
    BOOST_CHECK( elem_one.runtime_value()  == 9 );
}

BOOST_AUTO_TEST_CASE( canFindTypeInList )
{
    using test_list = ftl::list<ftl::size_t<2>, ftl::size_t<4>, ftl::int_t<6>>;
    
    std::size_t size_two_index  = ftl::find_type<ftl::size_t<2>, test_list>::result;
    std::size_t size_four_index = ftl::find_type<ftl::size_t<4>, test_list>::result;
    std::size_t int_six_index   = ftl::find_type<ftl::int_t<6>, test_list>::result;
    
    BOOST_CHECK( size_two_index   == 0 );
    BOOST_CHECK( size_four_index  == 1 );
    BOOST_CHECK( int_six_index    == 2 );
}

BOOST_AUTO_TEST_CASE( findTypeIsCorrectWhenTypeNotInList )
{
    using test_list             = ftl::list<ftl::size_t<3>, ftl::int_t<77>, ftl::size_t<12>>;
    using not_found_type        = ftl::find_type<ftl::int_t<9>, test_list>;
    
    int not_found_type_index    = not_found_type::result;
    
    BOOST_CHECK( not_found_type_index == -1 );
}

BOOST_AUTO_TEST_CASE( canCreateRange )
{
    using range = ftl::range<-4, 4, 2>::result;         // This makes a range [-4, 4, 2] of ftl::int_t types 
                                                        // and the range is just a list of the int_t types
    
    // So we should now have :
    // range = [ -4, -2, 0, 2, 4 ] or list< int_t<-4>, int_t<-2>, ..., int_t<4> >
    
    // Get some of the elements to test
    using range_0_type = ftl::get<0, range>;
    using range_2_type = ftl::get<2, range>;
    using range_4_type = ftl::get<4, range>;
    
    range_0_type range_0;           // Will be ftl::int_t< -4 > if correct
    range_2_type range_2;           // Will be ftl::int_t<  0 > if correct
    range_4_type range_4;           // Will be ftl::int_t<  4 > if correct
    
    // Since these are ftl::int_t elements, we can get their runtime values
    BOOST_CHECK( range_0.runtime_value() == -4 );
    BOOST_CHECK( range_2.runtime_value() ==  0 );
    BOOST_CHECK( range_4.runtime_value() ==  4 );
}

BOOST_AUTO_TEST_CASE( canZipListElementsWithEqualityEvaluator )
{ 
}

BOOST_AUTO_TEST_SUITE_END()
