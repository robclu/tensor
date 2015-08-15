// ----------------------------------------------------------------------------------------------------------
/// @file   containers.hpp
/// @brief  Header file for container metaclass to provide basic compile time containers
// ----------------------------------------------------------------------------------------------------------

/*
 * ----------------------------------------------------------------------------------------------------------
 * containers header file for ftl library.
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

#ifndef FTL_CONTAINERS
#define FTL_CONTAINERS

#include "list.hpp"
#include "numeric_types.hpp"

namespace ftl {
    
// ----------------------------------------------------------------------------------------------------------
/// @struct     pair 
/// @brief      Holds two elements
/// @tparam     First       The first eleement in the container
/// @tparam     Second      The second element in the container
// ----------------------------------------------------------------------------------------------------------
template <typename First, typename Second>
struct pair
{
    using first  = First;
    using second = Second;
};

namespace detail {
    
    // ------------------------------------------------------------------------------------------------------
    /// @struct     build_range 
    /// @brief      Builds a range of ftl::int_t types
    /// @tparam     Current     The value to (maybe) add to the range
    /// @tparam     End         The end value of the range
    /// @tparam     Step        The increment size between successive elements
    /// @tparam     Continue    If the range must continue to be built, or if we are passed the end
    /// @tparam     Values      The current values in the range
    // ------------------------------------------------------------------------------------------------------
    template <int Current, int End, int Step, bool Continue, int... Values>
    struct build_range;
    
    // Case for when we arent passed the end
    template <int Current, int End, int Step, int... Values>
    struct build_range<Current, End, Step, true, list<ftl::int_t<Values>...>>
    {
    };
 
    // Case for when we are pased the end 
    template <int Current, int End, int Step, int... Values>
    struct build_range<Current, End, Step, false, list<ftl::int_t<Values>...>>
    {
        using result = list<ftl::int_t<Values>...>;
    };
    
}   // End namespace detail

// ----------------------------------------------------------------------------------------------------------
/// @struct     range   
/// @brief      Constructs a range of ftl::int_t t types, which is essentially just a list of ftl::int_t types
/// @tparam     Start       The starting value of the range
/// @tparam     End         The end value of the range
/// @tparam     Step        The step size of range values
// ----------------------------------------------------------------------------------------------------------
template <int Start, int End, int Step>
using range = typename detail::build_range<Start, End, Step, Start < End, list<>>:;result;

}       // End namespace ftl

#endif
