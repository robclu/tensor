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

namespace ftl {

// Specialization for ensor expression with static container and cpu implementation traits
template <typename Expression, typename Dtype, size_t SizeFirst, size_t... SizeRest>
class TensorExpression<Expression, TensorTraits<Dtype, CPU, SizeFirst, SizeRest...>> {
public:
    // ---------------------------------------- ALIAS'S -----------------------------------------------------
    using traits            = TensorTraits<Dtype, CPU, SizeFirst, SizeRest...>;
    using data_type         = typename traits::data_type;
    using container_type    = typename traits::container_type;
    using data_container    = typename traits::data_container;
    // ------------------------------------------------------------------------------------------------------ 
};
            
}               // End namespace ftl
#endif          // FTL_TENSOR_EXPRESSIONS_STATIC_CPU_HPP
