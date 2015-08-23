// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for the functor which detrmines an index mapping for a tensor
// ----------------------------------------------------------------------------------------------------------

/*
 * ----------------------------------------------------------------------------------------------------------
 *  Header file for index mapper class
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

#ifndef FTL_INDEX_MAPPER_HPP
#define FTL_INDEX_MAPPER_HPP

#include <vector>
#include <numeric>

namespace ftl {
   
// ---------------------------------------------------------------------------------------------------------- 
/// @struct     index_mapper
/// @brief      Determines the offset in a tensor's memory given the index of an element in each of the
///             dimensions. So for example for a 2D tensor, or matrix), given element (2, 3) then the index 
///             mapper will determine that the element is at position 2 * num_columns + 3 ...
// ---------------------------------------------------------------------------------------------------------- 
struct index_mapper {
    template <typename I, typename... Is>
    size_t operator()(const std::vector<size_t>& dim_sizes, I idx, Is... indices) 
    {
        size_t offset = idx;
        // Call the map helper function to determine the rest of the offset
        return map_helper<1>(dim_sizes, offset, indices...);
    }
    
    template <size_t Iteration, typename I, typename... Is>
    size_t map_helper(const std::vector<size_t>&    dim_sizes   , 
                      size_t                        offset      ,       
                      I                             idx         , 
                      Is...                         indices     )
    {
        size_t num_indices = sizeof...(Is);
        offset += std::accumulate(dim_sizes.begin()                  ,
                                  dim_sizes.end() - num_indices - 1  ,
                                  1                                  , 
                                  std::multiplies<int>()             ) * idx;
        // Keep iterating
        return map_helper<Iteration + 1>(dim_sizes, offset, indices...);
    }
    
    // Case for when there are no more indices to add to offset
    template <size_t Iteration, typename I>
    size_t map_helper(const std::vector<size_t>&    dim_sizes   , 
                      size_t                        offset      ,
                      I                             idx         )
    {
        return offset + std::accumulate(dim_sizes.begin()         ,
                                        dim_sizes.end() - 1       ,
                                        1                         ,
                                        std::multiplies<int>()    ) * idx;
    }
};

}           // End namespace ftl

#endif      // FTL_INDEX_MAPPER_HPP
