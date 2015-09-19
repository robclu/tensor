// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor expression interface for tensor library.
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

#ifndef FTL_TENSOR_EXPRESSION_INTERFACE_HPP
#define FTL_TENSOR_EXPRESSION_INTERFACE_HPP

#include "tensor_traits.hpp"

namespace ftl {

// NOTE : All specializations are defined in their own files as:
//          - tensor_expressions_<container_type>_<device_type>,hpp
//          
//      : where
//          - container_type    = type of container (static_or dynamic)
//          - device_type       = type of device    (cpu gpu, any)
//          
//      any = not yet implemented for a specific device, or can operate on both


// ----------------------------------------------------------------------------------------------------------
/// @class      TensorExpression    
/// @brief      Defines a general tensor expression so that opertions on tensor expressions can be defined
///             the syntax of the operations to look as they would mathematically.
/// @tparam     Expression      The expression
/// @tparam     Traits          The traits which define the expression, for example specifying that the
///             expression uses static containers and GPU implemenations
// ----------------------------------------------------------------------------------------------------------
template <typename Expression, typename Traits>
class TensorExpression;

}           // End namespace ftl       
#endif      // FTL_TENSOR_EXPRESSION_INTERFACE_HPP
