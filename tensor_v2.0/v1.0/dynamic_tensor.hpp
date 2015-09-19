// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor library dynamic tensor class (worse performance, more flexibility)
// ----------------------------------------------------------------------------------------------------------

/*
* ----------------------------------------------------------------------------------------------------------
*  Header file for tensor library dynamic tensor class
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

#ifndef FTL_DYNAMIC_TENSOR_HPP
#define FTL_DYNAMIC_TENSOR_HPP

#include "tensor_container.hpp"
#include "tensor_expressions.hpp"

#include <initializer_list>

// Type alias defined at the bottom

namespace ftl {

// ----------------------------------------------------------------------------------------------------------
/// @class  dynamic_tensor 
/// @brief  A tensor implementation for when the sizes of the dimensions are not known when the tensor is
///         created and hence a dynamic container ,ust be used.
/// @tparam T       The type of data used by the tensor
// ----------------------------------------------------------------------------------------------------------
template <typename T>
class dynamicic_tensor : public tensor_expression<T, dynamic_tensor<T>> {
public:
    // ------------------------------------------- TYPEDEFS -------------------------------------------------
    using data_container = tensor_container<T>;
    using container_type = typename data_container::container_type;
    // ------------------------------------------------------------------------------------------------------
       
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Default constructor
    // ------------------------------------------------------------------------------------------------------ 
    dynamicic_tensor() {};
  
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Constructor for when the data is given as an lvalue 
    /// @param[in]  data    The data to use for the tensor
    // ------------------------------------------------------------------------------------------------------
    static_tensor(container_type& data)
    : _data(data) {}
   
private:
    data_container _data;                                   //!< The data container which holds all the data
    
};

template <typename T>
using dtensor = dynamic_tensor<T>;

}           // End namespace ftl

#endif      // FTL_DYNAMIC_TENSOR_HPP
