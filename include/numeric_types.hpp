// ----------------------------------------------------------------------------------------------------------
/// @file   numeric_types.hpp
/// @brief  Header file for static numeric types to use for meta functions
// ----------------------------------------------------------------------------------------------------------

/*
 * ----------------------------------------------------------------------------------------------------------
 * List header file for ftl library.
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
/// @struct     Size_t
/// @brief      Wrapper around size_t for static size_t types
/// @tparam     I       The value of the size_t type
// ----------------------------------------------------------------------------------------------------------
template <std::size_t I>
struct Size_t 
{
    // ------------------------------------------------------------------------------------------------------
    /// @brief  Gets the value of the tyoe at compile time
    // ------------------------------------------------------------------------------------------------------
    static constexpr std::size_t value = I;
   
    // -------------------------------------------------------------------------------------------------------
    /// @brief   Gets the value of the type at runtime
    /// @return  The value the type is holding
    // -------------------------------------------------------------------------------------------------------
    constexpr std::size_t runtimeValue() const { return I; }
};

// ----------------------------------------------------------------------------------------------------------
/// @struct     int
/// @brief      Wrapper around int for static int types
/// @tparam     I       The value of the int type
// ----------------------------------------------------------------------------------------------------------
template <int I>
struct Int_t 
{
    // ------------------------------------------------------------------------------------------------------
    /// @brief  Gets the value type at compile time
    // ------------------------------------------------------------------------------------------------------
    static constexpr int value = I;
    
    // -------------------------------------------------------------------------------------------------------
    /// @brief   Gets the value of the type at runtime
    /// @return  The value the type is holding
    // -------------------------------------------------------------------------------------------------------
    constexpr int runtimeValue() const { return I; }
};

// ----------------------------------------------------------------------------------------------------------
/// @namespace  dim
/// @brief      Defines Size_t types to use as dimension accessors in lists and tensors etc...
// ----------------------------------------------------------------------------------------------------------
namespace dim {
    
Size_t<0> i;
Size_t<1> j;
Size_t<2> l;
Size_t<3> m;

}       // End namespace dim

}       // End namespace ftl


#endif
