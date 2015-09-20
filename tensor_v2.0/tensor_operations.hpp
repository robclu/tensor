// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor operations for tensor library.
// ----------------------------------------------------------------------------------------------------------

/*
 * ----------------------------------------------------------------------------------------------------------
 *  Tensor is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Tensor is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with tensor; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * ----------------------------------------------------------------------------------------------------------
 */ 

#ifndef FTL_TENSOR_OPERATIONS_HPP
#define FTL_TENSOR_OPERATIONS_HPP

#include "tensor_addition.hpp"

// Unnamed namespace so that operations are available everywhere
namespace {

// ----------------------------------------------------------------------------------------------------------    
/// @brief      Adds two tensor expressions
/// @param[in]  x   The first expression to add
/// @param[in]  y   The second expression to add
/// @return     The result of the addition of the two tensor_expressions.
/// @tparam     E1  The type of the first expression for the addition
/// @tparam     E2  The type of the second expression for the addition
/// @tparam     T1  The traits of the first tensors -- for addition the traits for the returned tensor are 
///             the same as the first tensor for additio
/// @tparam     T2  The traits of the second expression
// ----------------------------------------------------------------------------------------------------------    
template <typename E1, typename E2, typename T1, typename T2>
const ftl::TensorAddition<E1, E2, T1, T2> operator+(ftl::TensorExpression<E1, T1> const& x, 
                                                    ftl::TensorExpression<E2, T2> const& y)    
{
    return ftl::TensorAddition<E1, E2, T1, T2>(x, y);
}

}           // End unnamed namespace    
#endif      // FTL_TENSOR_OPERATIONS_HPP
