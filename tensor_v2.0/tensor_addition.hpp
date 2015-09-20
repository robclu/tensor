// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor addition for tensor library.
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

#ifndef FTL_TENSOR_ADDITION_HPP
#define FTL_TENSOR_ADDITION_HPP

#include "tensor_expressions.hpp"

namespace ftl {

// ----------------------------------------------------------------------------------------------------------
/// @class      TensorAddition
/// @brief      Expression class for calculating the addition of two tensors.
/// @tparam     E1      The first expression for addition
/// @tparam     E2      The second expression for addition
/// @tparam     T1      The traits of the first expression
/// @tparam     T2      The traits if the second expression
// ----------------------------------------------------------------------------------------------------------
template <typename E1, typename E2, typename T1, typename T2>
class TensorAddition : public TensorExpression<TensorAddition<E1, E2, T1, T2>, T1> {
public:
    using traits            = T1;
    using dim_container     = typename traits::dim_container;
    using size_type         = typename traits::size_type;
    using data_type         = typename traits::data_type;
private:
    E1 const& _x;       //!< First expression for addition
    E2 const& _y;       //!< Second expression for addition
public:
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Sets the expressions for addition and checks that they have the same ranks and dimension
    /// @param[in] x       The first expression for addition.
    /// @param[in] y       The second expression for addition
    // ------------------------------------------------------------------------------------------------------
    TensorAddition(TensorExpression<E1, T1> const& x, TensorExpression<E2, T2> const& y); 

    // ------------------------------------------------------------------------------------------------------
    /// @brief     Gets the sizes of the all the dimensions of the expression.
    /// @return    A constant reference to the dimension size vector of the expression 
    // ------------------------------------------------------------------------------------------------------
    inline const dim_container& dim_sizes() const { return _x.dim_sizes(); }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Returns the size of the expression.
    /// @return    The size of the tensor_addition.
    // ------------------------------------------------------------------------------------------------------
    inline const size_type size() const { return _x.size(); }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Adds two elements (one from each Tensor) from the tensor expression data.
    /// @param[in] i   The element in the expression which must be fetched.
    /// @return    The result of the subtraction of the Tensors.
    // ------------------------------------------------------------------------------------------------------
    inline data_type operator[](size_type i) const { return _x[i] + _y[i]; }
};  

// ------------------------------------- ADDITION IMPLEMENTATIONS -------------------------------------------

template <typename E1, typename E2, typename T1, typename T2>
TensorAddition<E1, E2, T1, T2>::TensorAddition(const TensorExpression<E1, T1>& x, 
                                               const TensorExpression<E2, T2>& y) 
: _x(x), _y(y)
{
    // TODO: Add error throwing
    // Check that the ranks are equal
    if (x.rank() != y.rank() && x.dim_sizes() != y.dim_sizes()) ;
        // Throw error here 
}

}           // End namespace ftl  
#endif      // FTL_TENSOR_ADDITION_HPP
