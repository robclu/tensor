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

}       // End namespace ftl

#endif
