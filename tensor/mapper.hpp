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
    
    template <typename Index, typename DimList, typename PrevDimSizes>
    struct offset_calculator;
   
    // Case for the very first iteration, no previous dimensinos
    template <typename Index, typename Head, typename... Tail, typename... PrevDimSizes>
    struct offset_calucator<Index, nano::list<Head, Tail...>, empty_list>>
    {
        static constexpr int offset = 
            Index::value                            +
            offset_calculator<Index                 ,   // Offset from the other dimensions 
                              nano::list<Tail...>   , 
                              nano::list<Head>      ,   // Current dim size is passed as previoud dim size
                                  >::offset;
    };
           
    // Case for all cases but the first and last  
    template <typename Index, typename Head, typename... Tail, typename... Passed>
    struct offset_calculator<Index, nano::list<Head, Tail...>, nano::list<Passed...>>
    {
       static constexpr int offset =
           nano::multiplies<nano::list<PrevDimSizes...>>::result
    };
    
    // Base case
    template <typename Index, typename... Tail, typename... Passed>
    struct offset_calculator<Index, nano::empty_list, nano::list<Passed>>
    {
        
    };
    
    // -------------------------
    
    template <int       Iteration = 0   , 
              typename  Index           , 
              typename  AllDimSizes     , 
              typename  PrevDimSizes    , 
              typename  MappedIndices   >
    struct index_calculator;
    
    template <int           Iteration       ,
              typename      Index           , 
              typename      Head1           , 
              typename...   Tail1           , 
              typename...   PrevSizes       ,
              typename...   MappedIndices   >
    struct index_calculator<Iteration                   ,
                            Index                       ,   // Index in the contiguous memory space
                            nano::list<Head1, Tail1...> ,   // List of dimension sizes 
                            nano::list<PrevSizes...>    ,   // List of dimension sizes from previous iters
                            nano::list<MappedIndices...>>   // List of mapped indices
    {
        // Get the product of the dim sizes of the previous iterations
        static constexpr int prev_product =
            nano::multiplies<nano::list<PrevSizes...>>::result;
        
        // Base return result on the iterations 
        using new_index = typename std::conditional<
                                Iteration == 0                                                              , 
                                nano::int_t<Index::value % Head1::value>                                    ,
                                nano::int_t<(Index::value % (prev_product * Head1::value)) / prev_product   >
                                    >::type;
        
        // Add the new index to the list and recurse
        using result = typename index_calculator<  Iteration + 1                    , 
                                                   Index                            , 
                                                   nano::list<Tail1...>             ,
                                                   nano::list<Head1, PrevSizes...>  ,
                                                   nano::list<MappedIndices..., new_index>
                                                       >::result
        
    };
    
    // Terminating case

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

