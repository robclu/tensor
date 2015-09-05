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
#include <array>

namespace ftl {
    
// Helper meta functions for the mapper namespace
namespace detail {
    
    // ------------------------------------------------------------------------------------------------------
    /// @struct     index_calculator
    /// @brief      Takes an index of an element in contiguous memory, and using the mapping of that memory
    ///             space to dimensions, determines the index in each of the dimensions of the given index. 
    ///             For example, if a 3x3 matrix is stored column-major in memory, then index 4 in contiguous 
    ///             memory (0 indexing) maps to row 1 column 1. This metafunction, however, does the 
    ///             calculation for any dimensional structure at compile time.
    /// @tparam     Index           The index of the element in contiguous memory.
    /// @tparam     AlDimSizes      The sizes of all dimensions of the structure.
    /// @tparam     Iteration       The iteration of the calculation.
    /// @tparam     PrevDimSizes    The sizes of the dimensions used in previous iterations.
    /// @tparam     MappedIndices   The determined mapped indices.
    // ------------------------------------------------------------------------------------------------------
    template <typename  Index           				,
  			  typename  AllDImSizes						,
  			  int 		Iteration = 0   				,
              typename  PrevDimSizes = nano::list<>    	, 
              typename  MappedIndices = nano::list<>  	>
    struct index_calculator;
    
    // Recursive case
    template <typename      Index           , 
  			  typename 	    Head			,
  			  typename... 	Tail			,
  			  int 			Iteration		,
              typename...   PrevSizes       ,
              typename...   MappedIndices   >
    struct index_calculator<Index                       ,   
                		    nano::list<Head, Tail...>   ,
  						    Iteration 					,
                            nano::list<PrevSizes...>    ,   
                            nano::list<MappedIndices...>>
    {
        // Get the product of the dim sizes of the previous iterations
        // which is the offset in contiguous memory
        static constexpr int prev_product =
            nano::multiplies<nano::list<PrevSizes...>>::result;
        
        // The case for the first iteration is different, so check for that
        using new_index = typename std::conditional<
                                Iteration == 0                                                              , 
                                nano::int_t<Index::value % Head::value>                                     ,
                                nano::int_t<(Index::value % (prev_product * Head::value)) / prev_product>
                                    >::type;
        
        // Add the new index to the list of mapped indices and recurse, 
        // eliminating the dimension size that was just used
        using result = typename index_calculator<  
                                            Index                            		, 
                              				nano::list<Tail...>						,   
                              				Iteration + 1 							,
                                            nano::list<Head, PrevSizes...>   		,
                                            nano::list<MappedIndices..., new_index>	
                                                    >::result;
        
    };
    
    // Terminating case, just return the list of mapped indices
    template <typename Index, int Iteration, typename... PrevSizes, typename... MappedIndices>
    struct index_calculator< 
                            Index                       ,
      						nano::list<>				,
  							Iteration					,
                            nano::list<PrevSizes...>    , 
                            nano::list<MappedIndices...>>
    {
        using result = nano::list<MappedIndices...>;
    };

}       // End namespace detail

// ----------------------------------------------------------------------------------------------------------
/// @namespace  mapper
/// @brief      Mapping functions for converting an index in contiguous memory to its index values in the
///             multi-dimensional space which the contiguous memory represents (a matrix for example), and 
///             also for the reverse operations.
// ----------------------------------------------------------------------------------------------------------
namespace mapper {

template <typename Index, typename DimSizeList>
using index_to_dim_positions = typename detail::index_calculator<Index, DimSizeList>::result;

// Same as the above function, but the runtime implementation 

// ----------------------------------------------------------------------------------------------------------
/// @brief      Takes an index of an element in contiguous memory and converts it to a list of indices which
///             represent the index but in a multidimensional space which the contiguous memory represents.
/// @param[in]  index           The index of the element in contigous memory
/// @param[in]  dim_sizes       The sizes of the dimensions of the tensor to map 
/// @param[in]  prev_dim_sizes  The sizes of the dimensions used for previous iterations 
/// @param[in]  index_list      The list of mapped indices from the index
/// @tparam     ArraySize       The size of the array (The same size as dim_sizes, so will be passed implcitly
/// @tparam     Iteration       The iteration of the fuction
// ----------------------------------------------------------------------------------------------------------
template <size_t ArraySize, size_t Iteration = 0>
std::array<size_t, ArraySize> index_to_index_list(size_t index                                      , 
                                                  std::array<size_t, ArraySize>     dim_sizes       ,   
                                                  std::array<size_t, ArraySize>     index_list      ,
                                                  std::vector<size_t>               prev_dim_sizes  =
                                                    std::vector<size_t>(Iteration)                  )
{
    // Multiply the sizes of the dimensions used in previous iterations 
    // which gives the offset in contig mem of the start of this dimension
    size_t prev_product = std::accumulate(prev_dim_sizes.begin()        , 
                                          prev_dim_sizes.end()          , 
                                          1                             , 
                                          std::multiplies<size_t>()     );
    
    index_list[Iteraion] = std::conditional< Iteration == 0         ,
                                         index % dim_sizes[0]   ,
                                         (index % (prev_product * dim_sizes[Iteration])) / prev_product>;
    
    // Create new prev dim sizes
    prev_dim_sizes.push_back(dim_sizes[Iteration]);
    
    return std::conditional< Iteration == ArraySize , 
                             index_list             ,
                             index_to_index_list<Iteration + 1>(index, dim_sizes, index_list, prev_dim_sizes)>;
    
}
}           // End namespace mapper

}           // End namespace ftl

#endif      // FTL_MAPPER_HPP

