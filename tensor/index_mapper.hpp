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
class index_mapper {
public: 
    // ------------------------------------------------------------------------------------------------------
    // ------------------------------------------------------------------------------------------------------
    template <typename I, typename... Is>
    size_t operator()(const std::vector<size_t>& dim_sizes  , 
                      size_t iter  = 0                      , 
                      size_t index = 0                      , 
                      I idx                                 , 
                      Is... indices                         )
    {
        size_t num_indices = sizeof...(Is);     
        if (iter == 0) {                                    // First dimension, offset is simply the index
            index = idx;
        } else {                                            // Other cases
            index += std::accumulate(dim_sizes.begin()                  ,
                                     dim_sizes.end() - num_indices - 1  ,
                                     1                                  , 
                                     std::multiplies<size_t>()          ) * idx;
        }
        return this->operator()(dim_sizes, iter + 1, index, indices...);   
    }
    
};

}           // End namespace ftl

#endif      // FTL_INDEX_MAPPER_HPP
