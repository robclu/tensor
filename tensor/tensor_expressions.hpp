// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for expression classes for the tensor library.
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

// ----------------------------------------------------------------------------------------------------------
//	NOTES:
//		- The following conventions are used for brevity
//			: E		: Means Expression when used as a template parameter
//			: T     : Means Type when used as a template parameter
// ----------------------------------------------------------------------------------------------------------

#ifndef FTL_TENSOR_EXPRESSIONS_HPP
#define FTL_TENSOR_EXPRESSIONS_HPP

#include "utils.hpp"

#include <nano/nano.hpp>

namespace ftl {

// ----------------------------------------------------------------------------------------------------------
//! @class      tesnsor_expression
//! @brief      Define a tensor expression, for example a tensor itself, addition, subtraction ... which can
//!             then be used by operators to make operations on Tensors look mathematic.
//! @tparam     T   The type of data the expression uses
//! @tparam     E   The type of exprssion (tensor, tensor_addition etc...)
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
    //! @return    The size of the tensor_expression
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

// ----------------------------------------------------------------------------------------------------------
/// @class      tensor_difference
/// @brief      Expression class for calculating the difference of two tensors.
/// @tparam     T       The type of the data used by the tensors.
/// @tparam     E1      Expression to subtract from.
/// @tparam     E2      Expression to subtract with.
// ----------------------------------------------------------------------------------------------------------
template <typename T, typename E1, typename E2>
class tensor_difference : public tensor_expression<T, tensor_difference<T,E1,E2>> {
public:
    using typename tensor_expression<T, tensor_difference<T,E1,E2>>::container_type;
    using typename tensor_expression<T, tensor_difference<T,E1,E2>>::size_type;
    using typename tensor_expression<T, tensor_difference<T,E1,E2>>::value_type;
private:
    E1 const& _x;                                                   //!< First expression for subtraction
    E2 const& _y;                                                   //!< Second expression for subtraction
public:
    // ------------------------------------------------------------------------------------------------------
    /// @brief         Constructs a tensor_difference class from the inputs.
    /// @tparam[in]    x   The first expression for subtraction
    /// @tparam[in]    y   The second expression for subtraction
    // ------------------------------------------------------------------------------------------------------
    tensor_difference(tensor_expression<T,E1> const& x, tensor_expression<T,E2> const& y) : _x(x), _y(y) 
    { 
        ASSERT(x.size(), ==, y.size());                         // Check total sizes
        for (int i = 0; i < x.dim_sizes().size(); i++) {         // Check each dimension size
            ASSERT(x.dim_sizes()[i], ==, y.dim_sizes()[i]);
        }
    }
       
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Gets the sizes of the all the dimensions of the expression.
    /// @return    A constant reference to the dimension size vector of the expression 
    // ------------------------------------------------------------------------------------------------------
    const std::vector<size_type>& dim_sizes() const { return _x.dim_sizes(); }
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Returns the size of the expression
    /// @return    The size of the tensor_expression
    // ------------------------------------------------------------------------------------------------------
    size_type size() const { return _x.size(); }
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Subtracts two elements (one from each Tensor) from the Tensor expression data.
    /// @param[in] i   The element in the expression which must be fetched.
    /// @return    The result of the subtraction of the Tensors.
    // ------------------------------------------------------------------------------------------------------
    value_type operator[](size_type i) const { return _x[i] - _y[i]; }
};      

// ----------------------------------------------------------------------------------------------------------
/// @class      tensor_addition
/// @brief      Expression class for calculating the addition of two tensors.
/// @tparam     T       Type of the data used by the tesors
/// @tparam     E1      Expression to add to.
/// @tparam     E2      Expression to add with.
// ----------------------------------------------------------------------------------------------------------
template <typename T, typename E1, typename E2>
class tensor_addition : public tensor_expression<T, tensor_addition<T, E1, E2>> {
public:
    using typename tensor_expression<T, tensor_addition<T, E1, E2>>::container_type;
    using typename tensor_expression<T, tensor_addition<T, E1, E2>>::size_type;
    using typename tensor_expression<T, tensor_addition<T, E1, E2>>::value_type;
private:
    E1 const& _x;                                                   //!< First expression for addition
    E2 const& _y;                                                   //!< Second expression for addition
public:
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Sets the expressions for addition and checks that they have the same ranks and dimension
    ///            sizes.
    /// @param[in] x       The first expression for addition.
    /// @param[in] y       The second expression for addition
    // ------------------------------------------------------------------------------------------------------
    tensor_addition(tensor_expression<T,E1> const& x, tensor_expression<T,E2> const& y) : _x(x), _y(y) 
    { 
        ASSERT(x.size(), ==, y.size());                         // Check total sizes
        for (int i = 0; i < x.dim_sizes().size(); i++) {         // Check each dimension size
            ASSERT(x.dim_sizes()[i], ==, y.dim_sizes()[i]);
        }
    }
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Gets the sizes of the all the dimensions of the expression.
    /// @return    A constant reference to the dimension size vector of the expression 
    // ------------------------------------------------------------------------------------------------------
    const std::vector<size_type>& dim_sizes() const { return _x.dim_sizes(); }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Returns the size of the expression.
    /// @return    The size of the tensor_addition.
    // ------------------------------------------------------------------------------------------------------
    size_type size() const { return _x.size(); }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Adds two elements (one from each Tensor) from the Tensor expression data.
    /// @param[in] i   The element in the expression which must be fetched.
    /// @return    The result of the subtraction of the Tensors.
    // ------------------------------------------------------------------------------------------------------
    value_type operator[](size_type i) const { return _x[i] + _y[i]; }
};  

// ----------------------------------------------------------------------------------------------------------
/// @class      tensor_multipler
/// @brief      Expression which essentially just captures the arguments passed to the constructor, which will
///             be a list of dimensions to multiply over. It is a helper class for tensor_multiplication.
/// @tparam     T       Type of the data used by the Tensors.
/// @tparam     E1      Expression to multiply.
// ----------------------------------------------------------------------------------------------------------
template <typename T, typename E1, typename I, typename... Is>
class tensor_multiplier : public tensor_expression<T, tensor_multiplier<T, E1, I, Is...>> {
public:
    using typename tensor_expression<T, tensor_multiplier<T, E1, I, Is...>>::container_type;
    using typename tensor_expression<T, tensor_multiplier<T, E1, I, Is...>>::size_type;
    using typename tensor_expression<T, tensor_multiplier<T, E1, I, Is...>>::value_type;
    
    // Define a list of index values to multiply over
    using index_list = nano::list< typename  I::type, typename Is::type...>;
private:
    E1 const&       _x;                                 //!< Expression for multiplication
public:
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Sets the expression for multiplication
    /// @param[in]  x       The expression for multiplication
    // ------------------------------------------------------------------------------------------------------
    tensor_multiplier(tensor_expression<T, E1> const& x) : _x(x) {}
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the sizes of the all the dimensions of the expression.
    /// @return     A constant reference to the dimension size vector of the expression.
    // ------------------------------------------------------------------------------------------------------
    const std::vector<size_type>& dim_sizes() const { return _x.dim_sizes(); }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Returns the size of the expression.
    /// @return     The size of the tensor_multiplier.
    // ------------------------------------------------------------------------------------------------------
    size_type size() const { return _x.size(); }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Multiplies two elements (one from each Tensor) from the Tensor expression data.
    /// @param[in]  i   The element in the expression which must be fetched.
    /// @return     The result of the multiplication of the Tensors.
    // ------------------------------------------------------------------------------------------------------
    value_type operator[](size_type i) const { return _x[i]; }
};    

// ----------------------------------------------------------------------------------------------------------
/// @class      tensor_multiplication
/// @brief      Expression which takes two expressions (helper expressions) and does the multiplication 
/// @tparam     T       Type of the data used by the expressions
/// @tparam     E1      The first expression to multiply
/// @tparam     E2      THe second expression to multiply
// ----------------------------------------------------------------------------------------------------------
template <typename T, typename E1, typename E2>
class tensor_multiplication : public tensor_expression<T, tensor_multiplication<T, E1, E2>> {
public:
    using typename tensor_expression<T, tensor_multiplication<T, E1, E2>>::container_type;
    using typename tensor_expression<T, tensor_multiplication<T, E1, E2>>::size_type;
    using typename tensor_expression<T, tensor_multiplication<T, E1, E2>>::value_type;
    
    // Define some lists from the two expressions, that will be needed for doing eienstein reduction
    // 
    // Consider we have E1 = A, E2 = B and we want the result C_ik = A_ij * B_ji, then 
    // 
    // common_dims  : j -- since j is common to both 
    // exp_one_dims : i -- since i is uncommon to both, but present in E1
    // exp_two_dims : k -- since k is uncommon to both, but present in E2
    using common_dims   = typename nano::find_common<   typename E1::index_list, 
                                                        typename E2::index_list>::result;
    using exp_one_dims  = typename nano::find_uncommon< typename E1::index_list, 
                                                        typename E2::index_list>::result;
    using exp_two_dims  = typename nano::find_uncommon< typename E2::index_list, 
                                                        typename E2::index_list>::result;
private:
    E1 const&               _x;                         //!< First expression for multiplication
    E2 const&               _y;                         //!< Second expression for multiplication
    std::vector<size_type>  _dim_sizes;                 //!< Sizes of the dimensions of the resulting tensor
public:
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Sets the expressions for multiplication
    /// @param[in]  x        The first expression for multiplication
    /// @param[in]  y        The second expression for multiplication
    // ------------------------------------------------------------------------------------------------------
    tensor_multiplication(tensor_expression<T, E1> const& x, tensor_expression<T, E2> const& y)
    : _x(x) ,_y(y)
    {}
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the sizes of the all the dimensions of the expression.
    /// @return     A constant reference to the dimension size vector of the expression.
    // ------------------------------------------------------------------------------------------------------
    const std::vector<size_type>& dim_sizes() const { return _x.dim_sizes(); }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Returns the size of the expression.
    /// @return     The size of the tensor_multiplier.
    // ------------------------------------------------------------------------------------------------------
    size_type size() const { return _x.size(); }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Multiplies two elements (one from each Tensor) from the Tensor expression data.
    /// @param[in]  i   The element in the expression which must be fetched.
    /// @return     The result of the multiplication of the Tensors.
    // ------------------------------------------------------------------------------------------------------
    value_type operator[](size_type i) const { return _x[i]; }
private:
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Determines the sizes of each of the dimensions for a new tensor
    // ------------------------------------------------------------------------------------------------------
    void determine_dim_sizes() 
    {
        
    }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Calculates the value of the element at the given index as a result of the multiplication
    /// @param      i   The index of the element for which the value must be determined
    /// @return     The value of the elements at the index i in the tensor which results from the
    ///             multiplication
    // ------------------------------------------------------------------------------------------------------
    T calculate_value(size_type i) const 
    {
        
        return T(0);
    }
};   

}   // End namespace ftl

// ------------------------------------ TENSOR OPERATIONS ---------------------------------------------------

namespace {

// ----------------------------------------------------------------------------------------------------------    
/// @brief      Subtracts two tensor_expressions
///
///             The expressions could be any type: tensor, tensor_addition ..., 
/// @param[in]  x   The tensor_expression to substract from.
/// @param[in]  y   The tensor_expression to subtract with. 
/// @return     The result of the subtraction of the two tensor_expressions.
/// @tparam     T   Type of data used by the expressions.
/// @tparam     E1  Type of the expression to subtract from.
/// @tparam     E2  Type of the expression to subtract with.
// ----------------------------------------------------------------------------------------------------------    
template <typename T, typename E1, typename E2>
ftl::tensor_difference<T, E1 ,E2> const operator-(ftl::tensor_expression<T, E1> const& x, 
                                                  ftl::tensor_expression<T, E2> const& y)    
{
    return ftl::tensor_difference<T, E1, E2>(x, y);
}

// ==========================================================================================================
// ----------------------------------------------------------------------------------------------------------    
/// @brief      Adds two tensor_expressions
///
///             The expressions could be any Tensor type: tensor, tensor_difference ...
/// @param[in]  x   The tensor_expression to add to.
/// @param[in]  y   The tensor_expression to add with.
/// @return     The result of the addition of the two tensor_expressions.
/// @tparam     T   The type of data used by the expressions.
/// @tparam     E1  The type of the expression to add to.
/// @tparam     E2  The type of the expression to add with.
// ----------------------------------------------------------------------------------------------------------    
template <typename T, typename E1, typename E2>
ftl::tensor_addition<T, E1 ,E2> const operator+(ftl::tensor_expression<T, E1> const& x, 
                                                ftl::tensor_expression<T, E2> const& y)    
{
    return ftl::tensor_addition<T, E1, E2>(x, y);
}

}		// End global namespace

#endif	// FTL_TENSOR_EXPRESSIONS_HPP
