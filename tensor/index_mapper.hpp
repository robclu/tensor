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

#include "tensor_exceptions.hpp"

#include <vector>
#include <numeric>

namespace ftl {
   
// ---------------------------------------------------------------------------------------------------------- 
/// @class      index_mapper
/// @brief      Determines the offset in a tensor's melmory given the index of an element in each of the
///             dimensions. So for example for a 2D tensor, or matrix), given element (2, 3) then the index 
///             mapper will determine that the element is at position 2 * num_columns + 3 ...
// ---------------------------------------------------------------------------------------------------------- 
class index_mapper {
public:
    // ------------------------------------------------------------------------------------------------------
    /// @brief  Gets the offset in an element specified by the indices, in a contiguous structure
    /// @param[in]  dim_sizes   The sizes of all the dimensions in the tensor
    /// @param[in]  idx         The index of the element in the current dimension to add to offset
    /// @param[in]  indices     The rest of the indices for which the offset has not been determined
    /// @tparam     I           The type of the idx variable
    /// @tparam     Is          The types of the rest of the index variables 
    /// @return     The offset of the index at the postition specified by the indices
    /// @throw      tensor_out_of_range     If the index is out of range for the dimension an error is thrown
    // ------------------------------------------------------------------------------------------------------
    template <typename I, typename... Is>
    size_t operator()(const std::vector<size_t>& dim_sizes, I idx, Is... indices) const
    {
        if (!valid_index(idx, 0, dim_sizes)) return 0;
        
        size_t offset = idx;
        // Call the map helper function to determine the rest of the offset
        return map_helper<1>(dim_sizes, offset, indices...);
    }
    
private:
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Recursive case helper function for the mapper, adds the offset due to the number of 
    ///             elements in one of the dimensions of the tensor
    /// @param[in]  dim_sizes   The sizes of all the dimensions in the tensor
    /// @param[in]  offset      The offset of the element at the given index positions
    /// @param[in]  idx         The index of the element in the current dimension to add to offset
    /// @param[in]  indices     The rest of the indices for which the offset has not been determined
    /// @tparam     I           The type of the idx variable
    /// @tparam     Is          The types of the rest of the index variables 
    /// @return     The offset of the index at the postition specified by the indices
    /// @throw      tensor_out_of_range     If the index is out of range for the dimension an error is thrown
    // ------------------------------------------------------------------------------------------------------
    template <size_t Iteration, typename I, typename... Is>
    size_t map_helper(const std::vector<size_t>&    dim_sizes   , 
                      size_t                        offset      ,       
                      I                             idx         , 
                      Is...                         indices     ) const
    {
        if (!valid_index(idx, Iteration, dim_sizes)) return 0;
        
        size_t num_indices = sizeof...(Is);
        offset += std::accumulate(dim_sizes.begin()                  ,
                                  dim_sizes.end() - num_indices - 1  ,
                                  1                                  , 
                                  std::multiplies<int>()             ) * idx;
        // Keep iterating
        return map_helper<Iteration + 1>(dim_sizes, offset, indices...);
    }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Terminating case helper function for the mapper, adds the offset due to the number of 
    ///             elements in one of the dimensions of the tensor
    /// @param[in]  dim_sizes   The sizes of all the dimensions in the tensor
    /// @param[in]  offset      The offset of the element at the given index positions
    /// @param[in]  idx         The index of the element in the current dimension to add to offset
    /// @tparam     I           The type of the idx variable
    /// @return     The offset of the index at the postition specified by the indices
    /// @throw      tensor_out_of_range     If the index is out of range for the dimension an error is thrown
    // ------------------------------------------------------------------------------------------------------
    template <size_t Iteration, typename I>
    size_t map_helper(const std::vector<size_t>&    dim_sizes   , 
                      size_t                        offset      ,
                      I                             idx         ) const
    {
        if (!valid_index(idx, Iteration, dim_sizes)) return 0;
        
        return offset + std::accumulate(dim_sizes.begin()         ,
                                        dim_sizes.end() - 1       ,
                                        1                         ,
                                        std::multiplies<int>()    ) * idx;
    }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Checks the if an index for a given dimension is valid
    /// @param[in]  idx     The index of the element in the dimension
    /// @param[in]  dim     The dimension in which the index is being searched
    /// @return     True if there was no error, otherwise false
    /// @throw      tensor_out_of_range  If the index is out of range for the dimension an error is thrown
    // ------------------------------------------------------------------------------------------------------
    bool valid_index(const size_t idx, const size_t dim, const std::vector<size_t>& dim_sizes) const
    {
        try {                                                                       
            if (idx >= dim_sizes[dim]) {           
                throw tensor_out_of_range(dim + 1, dim_sizes[dim], idx); 
            } else return true;
        } catch (tensor_out_of_range& e ) {
            std::cout << e.what() << std::endl;
            return false; 
        }     
    }
};

}           // End namespace ftl

#endif      // FTL_INDEX_MAPPER_HPP
