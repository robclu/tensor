// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for mapper related classes and variables for mapping linear indices to multiple 
///         dimensions and from mapping multiple dimensions to a linear index etc ...
// ----------------------------------------------------------------------------------------------------------

/*
 * ----------------------------------------------------------------------------------------------------------
 *  Header file for mapper class
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

#ifndef FTL_MAPPER_HPP
#define FTL_MAPPER_HPP

#include <nano/nano.hpp>

namespace ftl {
    
// Define a mapper class 
template <typename... Dims>
class mapper;

// Helper metafunctions 
namespace detail {
    
    template <typename Index, typename DimList, typename Passed>
    struct dim_calculator;
   
    template <typename Index, typename Head, typename... Tail, typename... Passed>
    struct dim_calculator<Index, nano::list<Head, Tail...>, nano::list<Passed...>>
    {
    };
    
    // Base case
    template <typename Index, typename... Tail, typename... Passed>
    struct dim_calculator<Index, nano::empty_list, nano::list<Passed>>
    {
        
    };

}
// Specialization for using the mapper class at compile time 
template <typename... Dims>
class mapper<nano::list<Dims...>> 
{  
    template <typename Index>
    struct to_multidim
    {
        
    }
    
    template <typename... Indices>
    struct to_index;
    
    // Specialize for a list
    tempalte <typename... Indices>
    struct to_index<nano::list<Indices...>>
    {
    };
};
    


}           // End namespace ftl

#endif      // FTL_MAPPER_HPP

