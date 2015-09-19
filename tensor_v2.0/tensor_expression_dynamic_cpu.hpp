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
    using data_type         = typename traits::data_type;
    using container_type    = typename traits::container_type;
    using data_container    = typename traits::data_container;
    // ------------------------------------------------------------------------------------------------------ 
};
            
}               // End namespace ftl
#endif          // FTL_TENSOR_EXPRESSIONS_DYNAMIC_CPU_HPP
