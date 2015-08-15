// ----------------------------------------------------------------------------------------------------------
/// @file   numeric_types.hpp
/// @brief  Header file for static numeric types to use for meta functions
// ----------------------------------------------------------------------------------------------------------

/*
 * ----------------------------------------------------------------------------------------------------------
 * Numeric types header file for ftl library.
 * Copyright (C) 2015 Rob Clucas
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * ----------------------------------------------------------------------------------------------------------
 */

#ifndef FTL_NUMERIC_TYPES
#define FTL_NUMERIC_TYPES

namespace ftl {
 
// ----------------------------------------------------------------------------------------------------------
/// @struct     size_t
/// @brief      Wrapper around size_t for static size_t types used by metaclass and metafunctions in ftl
/// @tparam     Value   The value of the size_t type
// ----------------------------------------------------------------------------------------------------------
template <std::size_t Value>
struct size_t 
{
    // ------------------------------------------------------------------------------------------------------
    /// @brief  Gets the value of the tyoe at compile time
    // ------------------------------------------------------------------------------------------------------
    static constexpr std::size_t value = Value;
   
    // -------------------------------------------------------------------------------------------------------
    /// @brief   Gets the value of the type at runtime
    /// @return  The value the type is holding
    // -------------------------------------------------------------------------------------------------------
    constexpr std::size_t runtime_value() const { return Value; }
};

// ----------------------------------------------------------------------------------------------------------
/// @struct     int_t
/// @brief      Wrapper around int for static int types used by metaclass and metafunctions in ftl
/// @tparam     Value   The value of the int type
// ----------------------------------------------------------------------------------------------------------
template <int Value>
struct int_t
{
    // ------------------------------------------------------------------------------------------------------
    /// @brief  Gets the value type at compile time
    // ------------------------------------------------------------------------------------------------------
    static constexpr int value = Value;
    
    // -------------------------------------------------------------------------------------------------------
    /// @brief   Gets the value of the type at runtime
    /// @return  The value the type is holding
    // -------------------------------------------------------------------------------------------------------
    constexpr int runtime_value() const { return Value; }
};

// ----------------------------------------------------------------------------------------------------------
/// @namespace  dim
/// @brief      Defines ftl::size_t types to use as dimension accessors in lists and tensors etc...
// ----------------------------------------------------------------------------------------------------------
namespace dim {
    
    ftl::size_t<0> i;
    ftl::size_t<1> j;
    ftl::size_t<2> l;
    ftl::size_t<3> m;

}       // End namespace dim

}       // End namespace ftl


#endif
