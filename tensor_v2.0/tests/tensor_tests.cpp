// ----------------------------------------------------------------------------------------------------------
/// @file   tensor_tests.cpp
/// @brief  Test suite for tensor tests 
// ----------------------------------------------------------------------------------------------------------

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
    #define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>

#include "../tensor.hpp"

BOOST_AUTO_TEST_SUITE( TensorSuite)
    
BOOST_AUTO_TEST_CASE( canCreateDynamicCpuTensor )
{
    // Define the type of the dynamic tensor using the general tensor type
    using dynamic_tensor_gen = ftl::Tensor<int, ftl::CPU>;
    
    // Define the type of the dynamic tensor using the specialized CPU definition
    using dynamic_tensor_cpu = ftl::DynamicTensorCpu<int>;
    
    // Create a container using the traits class
    //traits::container_type A;
    
    //BOOST_CHECK( A.size() == 6 );
}

// -------------------------------------------- STATIC CPU --------------------------------------------------

BOOST_AUTO_TEST_CASE( canCreateDefaultStaticCpuTensor )
{
    // Define the type of the static tensor using the general tensor type
    // This defines a rank 3 tensor with all dimensions sizes with a value of 2
    using static_tensor_gen = ftl::Tensor<int, ftl::CPU, 2, 2, 2>;
    
    // Define the type of the static tensor using the specialized CPU definition
    // This defines a rank 3 tensor with all dimensions sizes with a value of 2
    using static_tensor_cpu = ftl::StaticTensorCpu<int, 2, 2 ,2>;
 
    static_tensor_gen A;   
    static_tensor_cpu B;
    
    BOOST_CHECK( A.size() == 8 );
    BOOST_CHECK( B.size() == 8 );
}

BOOST_AUTO_TEST_CASE( canCreateStaticCpuTensorWithDataFromContainer )
{
    // Create data for the static tensor
    std::array<float, 6> data{ {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f} };
    
    // Create a container specifying the dimension sizes
    ftl::Tensor<float, ftl::CPU, 2, 3> A(data); 
    
    BOOST_CHECK( A.size()   == 6    );
    BOOST_CHECK( A[0]       == 1.0f );
    BOOST_CHECK( A[1]       == 2.0f );
    BOOST_CHECK( A[2]       == 3.0f );
    BOOST_CHECK( A[3]       == 4.0f );
    BOOST_CHECK( A[4]       == 5.0f );
    BOOST_CHECK( A[5]       == 6.0f );
}

BOOST_AUTO_TEST_CASE( canCreateStaticCpuTensorWithLiteralList )
{ 
    // Create a container specifying the dimension sizes
    ftl::Tensor<double, ftl::CPU, 2, 2> A{ 1.0, 2.0, 3.0, 4.0 };
    
    BOOST_CHECK( A.size()   == 4   );
    BOOST_CHECK( A[0]       == 1.0 );
    BOOST_CHECK( A[1]       == 2.0 );
    BOOST_CHECK( A[2]       == 3.0 );
    BOOST_CHECK( A[3]       == 4.0 );
}

BOOST_AUTO_TEST_CASE( canDetermineDimensionSizesCorrectly )
{ 
    std::array<double, 2> data{ 1.0, 2.0 };
    
    // Create a container specifying the dimension sizes
    ftl::StaticTensorCpu<int    , 2, 2> A{ 1, 2, 3, 4 };
    ftl::StaticTensorCpu<float  , 3, 3> B;
    ftl::StaticTensorCpu<double , 2   > C(data);
    
    auto a_dim_sizes = A.dim_sizes();
    auto b_dim_sizes = B.dim_sizes();
    auto c_dim_sizes = C.dim_sizes();
    
    BOOST_CHECK( a_dim_sizes[0] == 2 );
    BOOST_CHECK( a_dim_sizes[1] == 2 );
    BOOST_CHECK( b_dim_sizes[0] == 3 );
    BOOST_CHECK( b_dim_sizes[1] == 3 );
    BOOST_CHECK( c_dim_sizes[0] == 2 );
}

BOOST_AUTO_TEST_CASE( canGetAndSetElementOfStaticCpuTensor ) 
{
    ftl::Tensor<int, ftl::CPU, 2, 2> A{4, 3, 2, 1};
    
    // Set 2nd element of the tensor
    A(1, 0) = 12;
    
    // Get 2nd element of the tensor
    int element = A(1, 0);
    
    BOOST_CHECK( element == 12 );
}

BOOST_AUTO_TEST_CASE( mappingOfMultipleDimensionsIsCorrect )
{
    // Create a tensor and fill it with some data. Data values are the indecies of the element 
    // to show the mapping, however, 1 indexing is used since an integer value can't have leading 0's
    // so:
    //      value 111 = indices 0, 0, 0 for dim 0, 1, 2 respecively
    //      value 212 = indices 1, 0, 1 for dim 0, 1, 2 respectively
    ftl::StaticTensorCpu<int, 2, 2, 2> A{ 111, 211, 121, 221  , 
                                          112, 212, 122, 222  }; 
    
    BOOST_CHECK( A(0, 1, 1) == 122 );
    BOOST_CHECK( A(1, 0, 1) == 212 );
    BOOST_CHECK( A(1, 1, 0) == 221 );
    BOOST_CHECK( A(1, 0, 0) == 211 );
}

BOOST_AUTO_TEST_CASE( canInitializeAStaticCpuTensor )
{
    // Create a 2x2x2 tensor with initial value
    ftl::Tensor<int, ftl::CPU, 2, 2, 2> A{ 110, 120, 210, 220, 111, 121, 211, 221 };
    
    // Modify all values by initializing them all to 1
    A.initialize(1, 1);
    
    BOOST_CHECK( A(0, 0, 0) == 1 );
}

BOOST_AUTO_TEST_SUITE_END()
