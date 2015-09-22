// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor expressions dynamic container and cpu specialization for tensor library.
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

#ifndef FTL_TENSOR_EXPRESSIONS_DYNAMIC_CPU_HPP
#define FTL_TENSOR_EXPRESSIONS_DYNAMIC_CPU_HPP

#include "tensor_expression_interface.hpp"

namespace ftl {

// Specialization for tensor expression with dynamic container and cpu implemenation traits
template <typename Expression, typename Dtype>
class TensorExpression<Expression, TensorTraits<Dtype, CPU>> {
public:
    // ---------------------------------------- ALIAS'S -----------------------------------------------------
    using traits            = TensorTraits<Dtype, CPU>;
    using size_type         = typename traits::size_type;
    using data_type         = typename traits::data_type;
    using container_type    = typename traits::container_type;
    using data_container    = typename traits::data_container;
    using dim_container     = typename traits::dim_container;
    // ------------------------------------------------------------------------------------------------------

    // ------------------------------------------------------------------------------------------------------
    /// @brief     Gets a pointer to the expression.
    /// @return    A non-const pointer to the expression.
    // ------------------------------------------------------------------------------------------------------
    Expression* expression() { return static_cast<Expression*>(this); }
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Gets a const pointer to the expression.
    /// @return    A const pointer to the expression.
    // ------------------------------------------------------------------------------------------------------
    const Expression* expression() const { return static_cast<const Expression*>(this); }
   
    // ------------------------------------------------------------------------------------------------------
    //! @brief     Gets a reference to the Tensor expression.
    //! @return    A reference to the Tensor expression E.
    // ------------------------------------------------------------------------------------------------------
    operator Expression&() { return static_cast<Expression&>(*this); }

    // ------------------------------------------------------------------------------------------------------
    //! @brief     Gets a constant reference to the Tensor expression.
    //! @return    A constant reference to the Tensror expression E.
    // ------------------------------------------------------------------------------------------------------
    operator Expression const&() const { return static_cast<const Expression&>(*this); }

    // ------------------------------------------------------------------------------------------------------
    //! @brief     Returns the size of the expression
    //! @return    The size of the tensor_expression
    // ------------------------------------------------------------------------------------------------------
    size_type size() const { return expression()->size(); }

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Returns the rank of the expression
    /// @return     The rank of the expression
    // ------------------------------------------------------------------------------------------------------
    size_type rank() const { return expression()->rank(); }
    
    // ------------------------------------------------------------------------------------------------------
    //! @brief     Gets the sizes of the all the dimensions of the expression.
    //! @return    A constant reference to the dimension size vector of the expression 
    // ------------------------------------------------------------------------------------------------------
    const dim_container& dim_sizes() const { return expression()->dim_sizes(); }

    // ------------------------------------------------------------------------------------------------------
    //! @brief     Gets and element from the Tensor expression data.
    //! @param[in] i   The element in the expression which must be fetched.
    //! @return    The value of the element at position i of the expression data.
    // ------------------------------------------------------------------------------------------------------
    inline data_type& operator[](size_type i) { return expression()->operator[](i); }

    // ------------------------------------------------------------------------------------------------------
    //! @brief     Gets and element from the Tensor expression data.
    //! @param[in] i   The element in the expression which must be fetched.
    //! @return    The value of the element at position i of the expression data.
    // ------------------------------------------------------------------------------------------------------
    inline const data_type& operator[](size_type i) const { return expression()->operator[](i); }
};
            
}               // End namespace ftl
#endif          // FTL_TENSOR_EXPRESSIONS_DYNAMIC_CPU_HPP
