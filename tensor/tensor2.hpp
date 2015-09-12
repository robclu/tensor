// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor2 library tensor class
// ----------------------------------------------------------------------------------------------------------

/*
* ----------------------------------------------------------------------------------------------------------
*  Header file for tensor tensor2 class
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

#ifndef FTL_TENSOR2_HPP
#define FTL_TENSOR2_HPP

#include "tensor.hpp"

namespace ftl {
    
// Create a type alias for a tensor2 as a specialization of tensor with rank 2
template <typename T>
class tensor2 : public tensor<T, 2> {
public:
    tensor2()
    {
        std::cout << "Constructing\n";
    }
};

}           // End namespace ftl

#endif      // FTL_TENSOR2_HPP

