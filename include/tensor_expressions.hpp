// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for ftl tensor expression classes.
// ----------------------------------------------------------------------------------------------------------

/*
 * ----------------------------------------------------------------------------------------------------------
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

// ----------------------------------------------------------------------------------------------------------
//	NOTES:
//		- The following conventions are used for brevity
//			: E		: Means Expression when used as a template parameter
//			: T     : Means Type when used as a template parameter
// ----------------------------------------------------------------------------------------------------------

#ifndef FTL_TENSOR_EXPRESSIONS
#define FTL_TENSOR_EXPRESSIONS

namespace ftl {

// ----------------------------------------------------------------------------------------------------------
//! @class      TensorExpression 
//! @brief      Define a Tesnor expression, for example a Tensor itself, addition, subtraction ... which can
//!             then be used by operators to make operations on Tensors look mathematic.
//! @tparam     T   The type of data the expression uses
//! @tparam     E   The type of exprssion (Tensor, TensorAddition etc...)
// ----------------------------------------------------------------------------------------------------------
template <typename T, typename E>
class tensor_expression {
public:
    // ----------------------------------------------- Typedefs ---------------------------------------------
    typedef std::vector<T>                      container_type;
    typedef typename container_type::size_type  size_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::reference  reference;
    // ------------------------------------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------------------------------------
    //! @brief     Returns the size of the expression
    //! @return    The size of the TensorExpression
    // ------------------------------------------------------------------------------------------------------
    size_type size() const { return static_cast<E const&>( *this ).size(); }

    // ------------------------------------------------------------------------------------------------------
    //! @brief     Gets the sizes of the all the dimensions of the expression.
    //! @return    A constant reference to the dimension size vector of the expression 
    // ------------------------------------------------------------------------------------------------------
    const std::vector<size_type>& dim_sizes() const { return static_cast<E const&>( *this ).dim_sizes(); }
    
    // ------------------------------------------------------------------------------------------------------
    //! @brief     Gets and element from the Tensor expression data.
    //! @param[in] i   The element in the expression which must be fetched.
    //! @return    The value of the element at position i of the expression data.
    // ------------------------------------------------------------------------------------------------------
    value_type operator[]( size_type i ) const { return static_cast<E const&>( *this )[i]; }

    // ------------------------------------------------------------------------------------------------------
    //! @brief     Gets a reference to the Tensor expression.
    //! @return    A reference to the Tensor expression E.
    // ------------------------------------------------------------------------------------------------------
    operator E&() { return static_cast<E&>( *this ); }

    // ------------------------------------------------------------------------------------------------------
    //! @brief     Gets a constant reference to the Tensor expression.
    //! @return    A constant reference to the Tensror expression E.
    // ------------------------------------------------------------------------------------------------------
    operator E const&() const   { return static_cast<const  E&>( *this ); }
};

}		// End namespace ftl

#endif	// FTL_TENSOR_EXPRESSIONS
