// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor specialization with a dynamic container using the cpu.
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

#ifndef FTL_TENSOR_DYNAMIC_CPU_HPP
#define FTL_TENSOR_DYNAMIC_CPU_HPP

#include "tensor_expression_dynamic_cpu.hpp"        // NOTE: Only including expression specialization for 
                                                    //       dynamic cpu implementation -- all specializations
                                                    //       are provided by tensor_expressions.hpp 


// NOTE : Using long template names results in extremely bulky code, so the following abbreviations are
//        used to reduve the bulk for template parameters:
//          - DT    = Dtype         = data type
//          - SF    = SizeFirst     = size of first dimension
//          - SR    = SizeRest      = size of other dimensions
//          - CPU   = CPU           = CPU device used for computation
namespace ftl {

// Forward declaration of TensorInterface so that we can provide the specialization
template <typename Traits>
class TensorInterface;

// Type alias for dynamic cpu tensor to make the code more readable
template <typename DT>
using DynamicTensorCpu = TensorInterface<TensorTraits<DT, CPU>>;

// Specialization for a tensor using a dynamic container and CPU devices
template <typename DT>
class TensorInterface<TensorTraits<DT, CPU>> : public TensorExpression<DynamicTensorCpu<DT> , 
                                                                       TensorTraits<DT, CPU>> {   
public:
    // ---------------------------------------- ALIAS'S ----------------------------------------------------- 
    using traits            = TensorTraits<DT, CPU>;
    using container_type    = typename traits::container_type;
    // ------------------------------------------------------------------------------------------------------
};

}               // End namespace ftl
#endif          // FTL_TENSOR_DYNAMIC_CPU_HPP
