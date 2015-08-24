// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor library index class and idx namespace for tensor indices
// ----------------------------------------------------------------------------------------------------------

/*
 * ----------------------------------------------------------------------------------------------------------
 *  Header file for tensor index class and idx namespace
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

#ifndef FTL_TENSOR_INDEX_HPP
#define FTL_TENSOR_INDEX_HPP

#include <nano/nano.hpp>

namespace ftl {
 
// ----------------------------------------------------------------------------------------------------------
/// @class      index
/// @brief      Defines an index for a dimension of a tensor, so index i can be dimension 0 etc...
/// @tparam     Value   The value of the index, or which dimension it represents
// ----------------------------------------------------------------------------------------------------------
template <int Value>
struct index {
    // The value of the index, which can be used at 
    // compile time or in meta programming structs
    using type = nano::int_t<Value>;

    // ------------------------------------------------------------------------------------------------------
    /// @brief  Gets the value of the index
    /// @return The value of the index (which dimension it represents)
    // ------------------------------------------------------------------------------------------------------
    static constexpr int value() { return Value; }
};

// Holds some declared index values
namespace idx {
    
ftl::index<0> i;
ftl::index<1> j;
ftl::index<2> k;
ftl::index<3> l;
    
}           // End namespace idx

}           // End namespace ftl

#endif      // FTL_TENSOR_INDEX_HPP
