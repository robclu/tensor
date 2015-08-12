// ----------------------------------------------------------------------------------------------------------
/// @file   list.hpp
/// @brief  Header file for the list metaclass to provide compile time lists
// ----------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------
// NOTES:
//      - The following additional conventions (besides those in eval.hpp) are used:
//          : L     : Used to mean a List
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

#ifndef FTL_LIST
#define FTL_LIST

#include "eval.hpp"

namespace ftl {
 
// ----------------------------------------------------------------------------------------------------------
/// @struct     List
/// @brief      Meta class that holds types, and allows functions to be applied to the elements of the list 
///             using the internal apply struct.                                                             \n
///                                                                                                          \n
///             Usage:                                                                                       \n
///                                                                                                          \n
///             using ftl::dim;         \\ To get dimension types                                            \n
///             using list = List<i, j, k, l>;  \\ A list of dimensions                                      \n
///                                                                                                          \n
///             using shifted_list = list::apply<shift>;                                                     \n
///                                                                                                          \n
///             Where shift is some function which operates on a type in the list 
/// @tparam     Ts      The tyes of the elements in the list
// ----------------------------------------------------------------------------------------------------------
template <typename... Ts>
struct List
{
    // ------------------------------------------------------------------------------------------------------
    /// @struct     apply
    /// @brief      Uses the function F and applies the function to each element in the list
    /// @tparam     Function    The function to apply the the list elements
    // ------------------------------------------------------------------------------------------------------
    template <template <typename...> class Function>
    struct apply
    {
        using type = List<typename Eval<Function<Ts>, NoArgs>::value...>;
    };
};

// For an empty List
using EmptyList = List<>;

// ---------------------------------------- Operations on a List(s) -----------------------------------------

// ----------------------------------------------------------------------------------------------------------
/// @struct     FindType    
/// @brief      Find the index of a specific type in the list (it results the index of the first occurence). \n
///             If the type is not found then the value 'parameter' will be -1
/// @tparams    T       The type to find
/// @tparam     L       The list to find the type in
// ----------------------------------------------------------------------------------------------------------
template <typename T, typename L>
struct FindType;
    
// Case to recurse
template <typename T,  typename Head, typename... Tail>
struct FindType<T, List<Head, Tail...>>
{
    static constexpr std::size_t next_value = FindType<T, List<Tail...>>::value;
    
    // 'Move through list'
    static constexpr std::size_t value      = next_value >= 0 ? next_value + 1 : -1;
};

// Case for when the type is found
template <typename T, typename... Tail>
struct FindType<T, List<T, Tail...>>
{
    static constexpr std::size_t value = 0;
};

// Case for not found 
template <typename T>
struct FindType<T, EmptyList>
{
    static constexpr std::size_t value = -1;
};

// ----------------------------------------------------------------------------------------------------------
/// @struct     Join
/// @brief      Joins two lists
/// @tparam     L1      The first list to join
/// @tparam     L2      The second list to join
// ----------------------------------------------------------------------------------------------------------
template <typename L1, typename L2>
struct Join;

// Specialization for using List types
template <typename... Ts, typename... Us>
struct Join<List<Ts...>, List<Us...>> : public Identify<List<Ts..., Us...>> {};


}   // End namespace ftl

#endif
