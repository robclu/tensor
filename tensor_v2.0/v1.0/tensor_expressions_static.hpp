// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for static expression classes for the tensor library.
// ----------------------------------------------------------------------------------------------------------

/*
 * ----------------------------------------------------------------------------------------------------------
 *  Tensor expressions header file for tensor library.
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
 * ----------------------------------------------------------------------------------------------------------
 */ 

#ifndef FTL_TENSOR_EXPRESSION_STATIC_HPP
#define FTL_TENSOR_EXPRESSION_STATIC_HPP

#include "tensor_container.hpp"

namespace ftl {

enum class tensor_type {
DYNAMIC    ,
STATIC     
};

// Define new tensor expression
template <typename Expression, class Traits>
class tensor_expression_new;

// Specialization for static tensors
template <typename Expression>
class tensor_expression_new<T, Expression, tensor_traits<tensor_type::STATIC>> {
public:
    // ----------------------------------------------- TYPEDEFS ---------------------------------------------
    using data_type         = T;
    using container_type    = typename Expression::container_type;
    using data_container    = typename Expression::data_container;
    using dim_container     = typename Expression::dim_container;
    // ------------------------------------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Gets a pointer to the expression.
    /// @return    A non-const pointer to the expression.
    // ------------------------------------------------------------------------------------------------------
    Expression*  expression() { return static_cast<Expression*>(this); }

    // ------------------------------------------------------------------------------------------------------
    /// @brief     Gets a const pointer to the expression.
    /// @return    A const pointer to the expression.
    // ------------------------------------------------------------------------------------------------------
    const Expression* expression() const { return static_cast<const Expression*>(this); }    
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Returns the size of the expression
    /// @return    The size of the expression
    // ------------------------------------------------------------------------------------------------------
    constexpr size_t size() const { return Expression::size(); }

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Returns the rank of the expression
    /// @return     The rank of the expression
    constexpr size_t rank() const { return Expression::rank(); }
    
    // ------------------------------------------------------------------------------------------------------
    //! @brief     Gets the sizes of the all the dimensions of the expression.
    //! @return    A constant reference to the dimension size vector of the expression 
    // ------------------------------------------------------------------------------------------------------
    //constexpr const dim_container& dim_sizes() const { return expression()->dim_sizes(); }
    
    // ------------------------------------------------------------------------------------------------------
    //! @brief     Gets and element from the Tensor expression data.
    //! @param[in] i   The element in the expression which must be fetched.
    //! @return    The value of the element at position i of the expression data.
    // ------------------------------------------------------------------------------------------------------
    inline data_type& operator[](size_t i) const { return expression()->operator[](i); }
};

}

#endif      // FTL_TENSOR_EXPRESSION_STATIC_HPP
