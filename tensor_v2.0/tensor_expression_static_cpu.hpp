// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor expressions static container and cpu specialization for tensor library.
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

#ifndef FTL_TENSOR_EXPRESSIONS_STATIC_CPU_HPP
#define FTL_TENSOR_EXPRESSIONS_STATIC_CPU_HPP

#include "tensor_expression_interface.hpp"

// NOTE: Some of the template parameters are abbreviated as (IMHO) it looks cleaner, so:
//          - DT    = Dtype     = type of data used
//          - SF    = SizeFirst = size of the first dimension
//          - SR    = SizeRest  = sizes of the rest of the dimensions

namespace ftl {

// Specialization for tensor expression with static container and cpu implementation traits
template <typename Expression, typename DT, size_t SF, size_t... SR>
class TensorExpression<Expression, TensorTraits<DT, CPU, SF, SR...>> {
public:
    // ---------------------------------------- ALIAS'S -----------------------------------------------------
    using traits            = TensorTraits<DT, CPU, SF, SR...>;
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
    /// @brief     Returns the size of the expression
    /// @return    The size of the expression
    // ------------------------------------------------------------------------------------------------------
    constexpr size_type size() const { return expression()->size(); }

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Returns the rank of the expression
    /// @return     The rank of the expression
    // ------------------------------------------------------------------------------------------------------
    constexpr size_type rank() const { return expression()->rank(); }
    
    // ------------------------------------------------------------------------------------------------------
    //! @brief     Gets the sizes of the all the dimensions of the expression.
    //! @return    A constant reference to the dimension size vector of the expression 
    // ------------------------------------------------------------------------------------------------------
    constexpr const dim_container& dim_sizes() const { return expression()->dim_sizes(); }

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
#endif          // FTL_TENSOR_EXPRESSIONS_STATIC_CPU_HPP
