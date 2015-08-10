/*
 *  Test file for fastRNN matrx class.
 *
 *  Copyright (C) 2015 Rob Clucas robclu1818@gmail.com
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <gtest/gtest.h>
#include <iostream>

#include "tensor.h"

TEST( frnnTensor, CanCreateTensorWithDefaultConstructor ) 
{
    frnn::Tensor<float, 3> tensor;
    EXPECT_EQ( tensor.size(), 0 );
}

TEST( frnnTensor, CanSpecifyTensorDimensionsWithList ) 
{
    frnn::Tensor<float, 2> tensor = {4, 3};
    EXPECT_EQ( tensor.size(), 12 );
}

TEST( frnnTensor, CanCreateTensorFromDimensionSizesAdnData )
{
    std::vector<size_t> dimension_sizes = {2, 3};
    std::vector<float>  data            = {1.f, 2.f,       // x0, x1, y0
                                           3.f, 4.f,       // x0, x1, y1
                                           5.f, 6.f};      // x0, x1, y2
    
    frnn::Tensor<float, 2> tensor(dimension_sizes, data);
    const std::vector<float>& tensor_data = tensor.data();
    
    EXPECT_EQ( tensor_data[1], 2.f );
}

TEST( frnnTensor, CanGetRankOfTensor ) 
{
    frnn::Tensor<float, 3> tensor = {1, 4, 4};
    
    int rank = tensor.rank();
    
    EXPECT_EQ( rank, 3 );
}

TEST( frnnTensor, CanGetTensorDimensions )
{
    frnn::Tensor<int, 3> tensor = {2, 1, 3};
    
    std::vector<size_t> dims = tensor.dimSizes();
    
    EXPECT_EQ( dims[0], 2 );
    EXPECT_EQ( dims[1], 1 );
    EXPECT_EQ( dims[2], 3 );
}

TEST( frnnTensor, CanGetSizeOfTensor ) 
{
    frnn::Tensor<double, 4> tensor = {2, 3, 2, 4};
    
    int size = tensor.size();
    
    EXPECT_EQ( size, 48 );
}

TEST( frnnTensor, CanGetSizeOfASpecificDimensionOfTensor ) 
{
    frnn::Tensor<float, 3> tensor = {1, 2, 3};
    
    int dim_size_0 = tensor.size(0);
    int dim_size_2 = tensor.size(2);
    
    EXPECT_EQ( dim_size_0, 1 );
    EXPECT_EQ( dim_size_2, 3 );
}

TEST( frnnTensor, CanHandleOutOfRangeIndexForSizeFunction ) 
{
    frnn::Tensor<int, 8> tensor = {1, 2, 4, 5, 3, 1, 1, 8};
    
    // Wrong due to 0 indexing
    int dim_size_8  = tensor.size(8);
    int dim_size_10 = tensor.size(10);
    
    EXPECT_EQ( dim_size_8 , 0 );
    EXPECT_EQ( dim_size_10, 0 );
}

TEST( frnnTensor, CanGetReferenceToTensorData ) 
{
    frnn::Tensor<float, 3> tensor_1       = {1, 2, 3};
    const std::vector<float>& tensor_data = tensor_1.data();
    
    EXPECT_EQ( tensor_data.size(), 6 );
    EXPECT_EQ( tensor_data[0], 0.f );
}

TEST( frnnTensor, CanAddTensors ) 
{
    frnn::Tensor<float, 3> tensor_1     = {1, 2, 3};
    frnn::Tensor<float, 3> tensor_2     = {1, 2, 3};
    frnn::Tensor<float, 3> tensor_3     = {1, 2, 3};
    frnn::Tensor<float, 3> new_tensor   = tensor_1 + tensor_2 + tensor_3;
    
    EXPECT_EQ( new_tensor.size(), tensor_1.size() );
}

TEST( frnnTensor, CanSubtractTensors ) 
{
    frnn::Tensor<float, 3> tensor_1     = {1, 2, 3};
    frnn::Tensor<float, 3> tensor_2     = {1, 2, 3}; 
    frnn::Tensor<float, 3> tensor_3     = {1, 2, 3}; 
    frnn::Tensor<float, 3> new_tensor   = tensor_1 - tensor_2 - tensor_3;
    
    EXPECT_EQ( new_tensor.size(), tensor_1.size() );
}

TEST( frnnTensor, CanAddAndSubtractTensors ) 
{
    frnn::Tensor<float, 3> tensor_1     = {1, 2, 3};
    frnn::Tensor<float, 3> tensor_2     = {1, 2, 3};
    frnn::Tensor<float, 3> tensor_3     = {1, 2, 3};
    frnn::Tensor<float, 3> new_tensor   = tensor_1 - tensor_2 + tensor_3;
    
    EXPECT_EQ( new_tensor.size(), tensor_1.size() );
}

TEST( frnnTensor, CanGetTensorRankAfterOperation )
{
    frnn::Tensor<int, 4> tensor_1 = {1, 2, 1, 1};
    frnn::Tensor<int, 4> tensor_2 = {1, 2, 1, 1};
    frnn::Tensor<int, 4> tensor_3 = tensor_1 - tensor_2;
    
    int rank = tensor_3.rank();
    
    EXPECT_EQ( rank, 4 );
}

TEST( frnnTensor, CanGetDimensionSizesAfterOperation ) 
{
    frnn::Tensor<int, 4> tensor_1 = {1, 2, 1, 1};
    frnn::Tensor<int, 4> tensor_2 = {1, 2, 1, 1};
    
    frnn::Tensor<int, 4> tensor_3   = tensor_1 - tensor_2;
    std::vector<size_t>  dims       = tensor_3.dimSizes();
    
    EXPECT_EQ( dims[ 0 ], 1 );
    EXPECT_EQ( dims[ 1 ], 2 );
    EXPECT_EQ( dims[ 2 ], 1 );
    EXPECT_EQ( dims[ 3 ], 1 );
}

TEST( frnnTensor, CanGetElementOfTensor ) 
{
    frnn::Tensor<float, 3> tensor = {2, 5, 4};
    
    float element = tensor(1, 3, 3);
    
    EXPECT_EQ( element, 0.f );
}

TEST( frnnTensor, CanSetElementOfTensor ) 
{
    frnn::Tensor<int, 3> tensor = {3, 3, 3};
    
    // Set 2nd element 
    tensor(1, 0, 0) = 4;
    
    // Get data 
    const std::vector<int>& tensor_data = tensor.data();
    
    EXPECT_EQ( tensor_data[1], 4 );
    EXPECT_EQ( tensor(1, 0, 0), 4 );
}

TEST( frnnTensor, ThrowsErrorForInvalidAccessOperatorArguments) 
{
    frnn::Tensor<double, 4> tensor = {4, 5, 3, 3};
    
    // Provide invalid number of arguments, 
    // should throw error and return 0
    double element = tensor(1, 1, 1, 1, 1);
    
    EXPECT_EQ( element, 0.0 );
} 

TEST( frnnTensor, ThrowsErrorForOutOfRangeElementAccess) 
{
    frnn::Tensor<int, 3> tensor = {3, 3, 3};
    
    // Access element 3 of dimension with size 3
    // (Tensor indexing is 0 based)
    int element_1 = tensor(1, 3, 2);
    int element_2 = tensor(4, 1, 1);
    int element_3 = tensor(1, 1, 5);
    
    EXPECT_EQ( element_1, 0 );
    EXPECT_EQ( element_2, 0 );
    EXPECT_EQ( element_3, 0 );
}

TEST( frnnTensor, CanCreateNewTensorFromSlice ) 
{
    using namespace frnn::index;
    frnn::Tensor<int, 3> tensor         = {3, 2, 3};
    frnn::Tensor<int, 2> sliced_tensor  = tensor.slice(j, i);
    
    // Check that dimensions were correctly swapped
    size_t slice_dim_size_i = sliced_tensor.size(0);    
    size_t slice_dim_size_j = sliced_tensor.size(1);
    
    EXPECT_EQ( slice_dim_size_i, tensor.size(1) );
    EXPECT_EQ( slice_dim_size_j, tensor.size(0) );
}

TEST( frnnTensor, CanCreateTensorMultiplier )
{
    frnn::Tensor<int, 2> tensor_1 = {2, 2};
    frnn::Tensor<int, 2> tensor_2 = {2, 2};

    using namespace frnn::index;
    frnn::TensorMultiplier<int, frnn::Tensor<int, 2>, frnn::Index> tensor_multiplier_1 = tensor_1(i, j);
    frnn::TensorMultiplier<int, frnn::Tensor<int, 2>, frnn::Index> tensor_multiplier_2 = tensor_2(j, k);
    
    frnn::TensorMultiplication<int,
                                frnn::TensorMultiplier<int, frnn::Tensor<int, 2>, frnn::Index>,
                                frnn::TensorMultiplier<int, frnn::Tensor<int, 2>, frnn::Index>,
                                4> 
                                    tmult(tensor_multiplier_1, tensor_multiplier_2);
                                   
    const std::vector<size_t> vect = tmult.dimSizes();
    
    std::vector<size_t> mapped = tmult.mapIndex(2);
    
    EXPECT_EQ( vect[0], 2 );
    EXPECT_EQ( vect[1], 2 );
    EXPECT_EQ( mapped[0], 0 );
    EXPECT_EQ( mapped[1], 1 );
}
