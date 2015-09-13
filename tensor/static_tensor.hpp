// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor library static tensor class (improved performance, less flexibility)
// ----------------------------------------------------------------------------------------------------------

/*
* ----------------------------------------------------------------------------------------------------------
*  Header file for tensor library static tensor class
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

#ifndef FTL_STATIC_TENSOR_HPP
#define FTL_STATIC_TENSOR_HPP

#include "tensor_container.hpp"
#include "tensor_expressions.hpp"

// Type alias defined at the bottom

namespace ftl {

template <typename T, size_t SF, size_t... SR>
class static_tensor : public tensor_expression<T, static_tensor<T, SF, SR...>> {
public:
    static_tensor() {};
private:
    using container_type = tensor_container<T, SF, SR...>;
    
    container_type _data;
    
};

template <typename T, size_t S1, size_t... SR>
using stensor = static_tensor<T, S1, SR...>;
}           // End namespace ftl

#endif      // FTL_STATIC_TENSOR_HPP