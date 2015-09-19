// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor interface for tensor library.
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

#ifndef FTL_TENSOR_INTERFACE_HPP
#define FTL_TENSOR_INTERFACE_HPP

#include "tensor_expressions.hpp"

namespace ftl {
    
template <typename Traits>
class TensorInterface;

template <typename Dtype, device DeviceType, size_t... DimSizes>
using DynamicTensor = TensorInterface<TensorTraits<Dtype, DeviceType, DimSizes...>>;

// Specialize for static tensors
template<typename Dtype, device DeviceType>
class Tensor : public TensorExpression<DynamicTensor<Dtype, DeviceType>, TensorTraits<Dtype, DeviceType>>
{        
    using traits            = TensorTraits<Dtype, DeviceType>;
    using container_type    = typename traits::container_type;
};

}               // End namespace ftl
#endif          // FTL_TENSOR_INTERFACE_HPP
