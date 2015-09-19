// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for mapper related classes and variables for mapping linear indices to multiple 
///         dimensions and from mapping multiple dimensions to a linear index etc for both static and dynamic 
///         containers
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

#ifndef FTL_CONTAINER_MAPPER_HPP
#define FTL_CONTAINER_MAPPER_HPP

#include <nano/nano.hpp>

#include <iostream>
#include <type_traits>
#include <utility>
#include <numeric>

namespace ftl {
    
namespace detail {

// ----------------------------------------------------------------------------------------------------------
/// @struct     map_to_index_static
/// @brief      Takes a list of indices and a list of dimension sizes, and determines the offset of an
///             element given by the indices, in contiguous memory
/// @tparam     DimSizes    The sizes of each of the dimensions
/// @tparam     Indices     The value of the element in each of the indices
// ----------------------------------------------------------------------------------------------------------
template <typename DimSizes, typename... Indices>
struct map_to_index_static;

// Recursive case
template <typename DimSizes, typename IF, typename... IR>
struct map_to_index_static<DimSizes, IF, IR...>
{
    // On each iteration the product of the size of all previous dimensions must be calculated
    // to determine the memory offset of this dimension, so determine the stopping index
    using end_index = typename std::conditional<
                        DimSizes::size - sizeof...(IR) == 1                     ,
                        typename nano::size_t<0>                                ,
                        typename nano::size_t<DimSizes::size - sizeof...(IR) - 2>>::type;
    
    // The product sum of the previous dimensions (previous iterations) so if we are on iteration
    // 3 then this is the product of the size of dimension 0 and 1
    static constexpr size_t dim_product_sum =
        nano::accumulate<DimSizes, 0, end_index::value, 1>::result;
    
    // The offset calculation 
    static constexpr size_t offset(size_t current_offset, IF&& index_first, IR&&... indices_rest) 
    {
        // Recursively call until the terminating case 
        // If first iteration use index_first as offset
        // if other iteration, add mult with prev products
        return DimSizes::size - sizeof...(IR) == 1 
             ? map_to_index_static<DimSizes, IR...>::offset(current_offset + index_first                    , 
                                                             std::forward<IR>(indices_rest)...              ) 
             : map_to_index_static<DimSizes, IR...>::offset(current_offset + index_first * dim_product_sum  , 
                                                            std::forward<IR>(indices_rest)...               );
    }
};

// Terminating (base) case
template <typename DimSizes>
struct map_to_index_static<DimSizes>
{
    // Just need to return the result here
    static constexpr size_t offset(size_t current_offset) { return current_offset; }
};

// Dynamic implementation

template <size_t Iteration, typename Container>
size_t map_to_index_dynamic(const Container&    dim_sizes       ,
                            size_t             current_offset  )
{
    return current_offset;
}

template <size_t Iteration, typename Container, typename IF, typename... IR>
size_t map_to_index_dynamic(const Container&    dim_sizes       , 
                            size_t              current_offset  , 
                            IF                  index_first     , 
                            IR...               indices_rest    )
{
    size_t num_indices = sizeof...(IR);
    current_offset += std::accumulate(dim_sizes.begin()                 ,
                                      dim_sizes.end() - num_indices - 1 ,
                                      1                                 ,
                                      std::multiplies<size_t>()         ) * index_first;
    // Keep iterating
    return map_to_index_dynamic<Iteration + 1>(dim_sizes, current_offset, indices_rest...);
}

}           // End namespace detail

// ----------------------------------------------------------------------------------------------------------
/// @struct     static_mapper
/// @brief      Interface which provides static mapping (uses TMP to determine some of the mapping variables 
///             at compile time for improved performance) from indices to a single offset index and from an 
///             index offset to a list of indices
// ----------------------------------------------------------------------------------------------------------
struct static_mapper {

// ----------------------------------------------------------------------------------------------------------
/// @brief      Maps any number of indices which represent the location of an index in a multi-dimensional
///             space, to a singe index offset in the contiguous memory which is representing that 
///             multi-dimensional space 
/// @param[in]  index_first     The index of the element in the first dimension 
/// @param[in]  indices_rest    The indices of the element in the other dimensions
/// @tparam     DimSizes        The list of dimension sizes for the multi-dimensional space
/// @tparam     IF              The type of index_first
/// @tparam     IR              The types of indices_rest
// ----------------------------------------------------------------------------------------------------------
template <typename DimSizes, typename IF, typename... IR>
static constexpr size_t indices_to_index(IF&& index_first, IR&&... indices_rest)
{
    return detail::map_to_index_static<DimSizes, IF, IR...>::offset(0                                   , 
                                                                    std::forward<IF>(index_first)       , 
                                                                    std::forward<IR>(indices_rest)...   );
}

};

struct dynamic_mapper {
  
template <typename Container, typename IF, typename... IR>
static size_t indices_to_index(const Container&     dim_sizes   ,  
                               IF                   index_first ,
                               IR...                indices_rest)
{
    return detail::map_to_index_dynamic<1>(dim_sizes, index_first, indices_rest...);
}

};

}           // End namespace ftl

#endif      // FTL_CONTAINER_MAPPER_HPP
