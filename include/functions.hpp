// ----------------------------------------------------------------------------------------------------------
/// @file   function.hpp
/// @brief  Header file for metafunctions to operator on compile time data structures
// ----------------------------------------------------------------------------------------------------------

/*
 * ----------------------------------------------------------------------------------------------------------
 * functions header file for ftl library.
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

#ifndef FTL_FUNCTIONS
#define FTL_FUNCTIONS

namespace ftl {

// ----------------------------------------------------------------------------------------------------------
/// @struct     equal_value 
/// @brief      Check if two types (which have value components) have the same value.
/// @tparam     Type1       The first type to check for equality
/// @tparam     Type2       The second type to check for equality
// ----------------------------------------------------------------------------------------------------------
template <typename Type1, typename Type2>
struct equal_value 
{
    static constexpr bool result = Type1::value == Type2::value ? true : false;
};

// ----------------------------------------------------------------------------------------------------------
/// @struct     is_found
/// @brief      If the type is found (has a value != -1 as per the library convention) then result is true,
///             otherwise result is false.
/// @tparam     Type        The type to determine if it is found
// ----------------------------------------------------------------------------------------------------------
template <typename Type>
struct 
{
    static constexpr bool result = Type::value != -1 ? true : false;
};

// ----------------------------------------------------------------------------------------------------------
/// @struct     both_found 
/// @brief      Checks if both types are found (have values != -1), in which case result is true, otherwise
///             result is false
/// @tparam     Type1       The first type to determine if it is found
/// @tparam     Type2       The second type to determine if it is found
// ----------------------------------------------------------------------------------------------------------
template <typename Type1, typename Type2>
struct both_found
{
    static constexpr bool result = ( (Type1::value != -1) && (Type2::value != -1) ) ? true : false;
};

};


#endif      // FTL_FUNCTIONS
