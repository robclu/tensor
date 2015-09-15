// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor library static tensor class (improved performance, less flexibility)
// ----------------------------------------------------------------------------------------------------------

/*
* ----------------------------------------------------------------------------------------------------------
*  Header file for tensor library static tensor class
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

#ifndef FTL_STATIC_TENSOR_HPP
#define FTL_STATIC_TENSOR_HPP

#include "mapper.hpp"
#include "tensor_container.hpp"
#include "tensor_expressions.hpp"

#include <initializer_list>

// Type alias defined at the bottom

namespace ftl {

// ----------------------------------------------------------------------------------------------------------
/// @class  static_tensor 
/// @brief  A tensor implementation for when the sizes of the dimensions can be specified as template params,
///         and hence allows the tensor to use static data containers and infer more properties about the
///         tensor. The performance is better than the dynamic tensor but is slightly less flexible
/// @tparam T       The type of data used by the tensor
/// @tparam SF      The size of the first dimension
/// @tparam SR      The size of the rest of the dimensions 
// ----------------------------------------------------------------------------------------------------------
template <typename T, size_t SF, size_t... SR>
class static_tensor : public tensor_expression<T, static_tensor<T, SF, SR...>> {
public:
    // --------------------------------------- TYPEDEFS -----------------------------------------------------
    using data_container        = tensor_container<T, SF, SR...>;
    using container_type        = typename data_container::container_type;
    using dimension_container   = typename nano::runtime_converter<
                                                typename data_container::dimension_sizes>::array_type;
    // ------------------------------------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Default constructor
    // ------------------------------------------------------------------------------------------------------
    static_tensor() 
    {
        // Convert the nano::list of dimension sizes to a constant array
        _dim_sizes = nano::runtime_converter<typename data_container::dimension_sizes>::to_array(); 
    };
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Constructor for when the data is given as an lvalue 
    /// @param[in]  data    The data to use for the tensor
    // ------------------------------------------------------------------------------------------------------
    static_tensor(container_type& data)
    : _data(data) 
    {
        // Convert the nano::list of dimension sizes to a constant array
        _dim_sizes = nano::runtime_converter<typename data_container::dimension_sizes>::to_array();
    }
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Constructor for when the data is specified as a literal list
    /// @param[in]  first_value     The first value in the literal list
    /// @param[in]  other_values    The rest of the values in the literal list
    /// @tparam     TF              The type of the first value
    /// @tparam     TR              The type of the rest of the values
    // ------------------------------------------------------------------------------------------------------
    template <typename TF, typename... TR> 
    static_tensor(TF&& first_value, TR&&... other_values) 
    : _data(std::forward<TF>(first_value), std::forward<TR>(other_values)...) 
    {
        // Convert the nano::list of dimension sizes to a constant array
        _dim_sizes = nano::runtime_converter<typename data_container::dimension_sizes>::to_array(); 
    }
 
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the rank (number of dimensions) of the tensor
    /// @return     The rank (number of dimensions) of the tensor
    // ------------------------------------------------------------------------------------------------------
    constexpr size_t rank() const { return sizeof...(SR) + 1; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the size (total number of elements) in the tensor
    /// @return     The size of the tensor
    // ------------------------------------------------------------------------------------------------------
    constexpr size_t size() const { return _data.size(); }
  
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets a reference to the container holding the sizes of the dimensions for the tensor
    /// @return     A constant reference to the dimension sizes of the tensor
    // ------------------------------------------------------------------------------------------------------
    constexpr const dimension_container& dim_sizes() const { return _dim_sizes; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets an element from the tensor
    /// @param[in]  i   The index of the element in the tensor
    /// @return     A reference to the element at the index i in the tensor
    // ------------------------------------------------------------------------------------------------------
    inline T& operator[](size_t i) { return _data[i]; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the element at a given index for each dimension of a tensor
    /// @param[in]  index_dim_one   The index of the element in dimension 1
    /// @param[in]  index_dim_other The index of the element in the other dimensions
    /// @tparam     Mapper          The functor used to determine the mapping 
    /// @tparam     IF              The type of the first index parameter
    /// @tparam     IR              The types of the rest of the index parameters
    // ------------------------------------------------------------------------------------------------------
    template <typename Mapper = mapper, typename IF, typename... IR>
    T& operator()(IF index_dim_one, IR... index_dim_other);
    
private:
    data_container              _data;                  //!< The data container which holds all the data
    dimension_container         _dim_sizes;             //!< The sizes of the dimensions for the tensor
};

// ----------------------------------------------- IMPLEMENTATIONS ------------------------------------------

template <typename T, size_t SF, size_t...SR> template <typename Mapper, typename IF, typename... IR>
T& static_tensor<T, SF, SR...>::operator()(IF dim_one_index, IR... other_dim_indices) 
{
    try {   // Check that the fiven number of params == rank
        if (sizeof...(IR) != sizeof...(SR))
            throw tensor_invalid_arguments(sizeof...(IR) + 1, sizeof...(SR) + 1);
    } catch (tensor_invalid_arguments& e) {
        std::cerr << e.what() << "\n";
        return _data[0];
    }
    return _data[mapper::index_list_to_index(_dim_sizes, dim_one_index, other_dim_indices...)];
}

// ------------------------------------------------- ALIAS'S ------------------------------------------------

template <typename T, size_t SF, size_t... SR>
using stensor = static_tensor<T, SF, SR...>;

}           // End namespace ftl

#endif      // FTL_STATIC_TENSOR_HPP
