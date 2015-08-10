// ==========================================================================================================
//! @file   Header file for fastRNN tensor util functions.
// ==========================================================================================================

/*
 * ==========================================================================================================
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
 * ==========================================================================================================
 */ 

#ifndef _FRNN_TENSOR_UTILS_
#define _FRNN_TENSOR_UTILS_

#include <vector>
#include <numeric>

namespace frnn {
namespace tensor {
    
// ==========================================================================================================
//! @struct     DimensionMapper 
//! @brief      Takes an index of an element in a new Tensor A which is a slice of an old Tensor B, and 
//!             determines the index in a dimension of the old Tensor A which can be used to fetch the 
//!             corresponding element for idx in B.                                                          \n
//!                                                                                                          \n
//!             Say A is a 2D Tensor with dimensions {2, 3}, so x = 2, y = 3, which is :                     \n
//!                                                                                                          \n
//!             A = [ x00 x01 ;                                                                              \n
//!                   x10 x11 ;                                                                              \n
//!                   x20 x21 ]                                                                              \n
//!                                                                                                          \n
//!             Then say that B = A(j, i) (in this case the transpose of A), then B will look like           \n
//!                                                                                                          \n
//!             B = [ x00 x10 x20 ;  = [ idx0 idx1 idx2 idx3 idx4 idx5 ] (in memory)                         \n
//!                   x01 x11 x21 ]                                                                          \n
//!                                                                                                          \n
//!             then the DimensionMapper functor, for a given idx, say idx2, determines the offset in a      \n
//!             dimension (i, or j in this case) of the element in A's memory which corresponds to idx2,     \n
//!             which in this case would be x20 from A, so the functor would get 0 for dimension i, and 2    \n
//!             for dimension j.
//! @tparam     iter    Which iteration of the index mapping the algorithm is on.
// ==========================================================================================================
template <size_t iter> struct DimensionMapper{
public:
     //======================================================================================================
     //! @brief     Determines the index of a dimension in a tensor which can be used to fetch the
     //!            element in that tensor corresponding to element idx in the calling Tensor.
     //! @param[in] idx             The index of the element to map in the calling Tensor.
     //! @param[in] dim_size        The size of the dimension in the original tensor for which the index
     //!            must be mapped.
     //! @param[in] prev_dim_size   The sizes of the dimensions for which the mappings have already been 
     //!                            determined.
     //! @return    A value of a dimension in a Tensor being mapped from which can be used to get the element
     //!            for position idx in the new Tensor.
     // =====================================================================================================
    size_t operator()(const size_t idx, const size_t dim_size, std::vector<size_t>& prev_dim_sizes) const 
    {
        // Computes the product of the previous dimensions sizes which were used by 
        // previous iterations, so if the previous dimension sizes were [2,3,1] then 
        // the product returns 6, which can be used to map idx to the tensor being sliced
        size_t prev_dim_sizes_product = std::accumulate(prev_dim_sizes.begin()       ,
                                                        prev_dim_sizes.end()         ,
                                                        1                            ,
                                                        std::multiplies<size_t>()    );
        
        return ((idx % (prev_dim_sizes_product * dim_size)) / prev_dim_sizes_product);
    }
};

template<> struct DimensionMapper<0> {
public:
     //======================================================================================================
     //! @brief     Determines the index of a dimension in a tensor which can be used to fetch the
     //!            element in that tensor corresponding to element idx in the calling Tensor, this is 
     //!            for the partially specialized instance of the DimensionMapper functor for the first 
     //!            iteration of the algorithm.
     //! @param[in] idx             The index of the element to map in the calling Tensor.
     //! @param[in] dim_size        The size of the dimension in the original tensor for which the index
     //!            must be mapped.
     //! @return    A value of a dimension in a Tensor being mapped from which can be used to get the element
     //!            for position idx in the new Tensor.
     // =====================================================================================================
    size_t operator()(const size_t idx, const size_t dim_size) const 
    {
        return idx % dim_size;
    }
};

}       // End namespace tensor
}       // End namespace frnn

#endif
