// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor library tensor_container class to allow both static and dynamic containers
// ----------------------------------------------------------------------------------------------------------

/*
* ----------------------------------------------------------------------------------------------------------
*  Header file for tensor tensor_container class
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

#ifndef FTL_TENSOR_CONTAINER_HPP
#define FTL_TENSOR_CONTAINER_HPP

#include <nano/nano.hpp>

#include <array>
#include <vector>
#include <iostream>

namespace ftl {
   
// ----------------------------------------------------------------------------------------------------------
/// @struct     tensor_container
/// @brief      Container for tensor data depending on if the tensor is static (dimension sizes, and hence the
///             total number of elements, known at compile time -- uses std::array) or dynamic (dimension 
///             sizes are not known at compile time -- uses std::vector).
/// @tparam     T       The type of data used by the tensor
/// @tparam     Sizes   The sizes of the dimensions (optional)
// ----------------------------------------------------------------------------------------------------------
template <typename T, size_t... Sizes>
class tensor_container;

// Specialize for static containers
template <typename T, size_t SizeFirst, size_t... SizeRest>
class tensor_container<T, SizeFirst, SizeRest...> {
public:
    // ------------------------------------ TYPEDEFS --------------------------------------------------------
    using dimension_sizes   = nano::list<nano::size_t<SizeFirst>, nano::size_t<SizeRest>...>;
    using dimension_product = nano::multiplies<dimension_sizes>;
    using container_type    = std::array<T, dimension_product::result>; 
    // ------------------------------------------------------------------------------------------------------

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Default constructor 
    // ------------------------------------------------------------------------------------------------------
    tensor_container() {}

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Contructor when given an array with the data for the container
    /// @param[in]  data    The data to use to initalize the container data with
    // ------------------------------------------------------------------------------------------------------
    constexpr tensor_container(container_type& data)
    : _data(data) {}

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Move constructor for when the data is given as a literal list
    /// @param[in]  first_value     The first value in the literal list 
    /// @param[in]  other_valeus    The rest of the values in the literal list
    /// @tparam     T1              The type of the first_value parameter
    /// @tparam     TR              The type of the rest of the parameters
    // ------------------------------------------------------------------------------------------------------
    template <typename T1, typename... TR> 
    constexpr tensor_container(T1&& first_value, TR&&... other_values) 
    : _data({first_value, other_values...}) {}

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the size (total number of elements) in the container
    /// @return     The size of the container
    // ------------------------------------------------------------------------------------------------------
    constexpr size_t size() const { return dimension_product::result; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets an element from the container
    /// @param[in]  i   The index of the element in the container
    /// @return     A reference to the element at the index i in the container
    // ------------------------------------------------------------------------------------------------------
    inline T& operator[](size_t i) { return _data[i]; }
private:
    container_type _data;                                                   //!< Static data for a tensor
};

// Specialization for dynamic container which the dimension sizes
// (and hence the number of elements) are not known at compile time
template <typename T>
class tensor_container<T> {
public:
    // -------------------------------- TYPEDEFS ------------------------------------------------------------
    using container_type = std::vector<T>;
 
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Default constructor 
    // ------------------------------------------------------------------------------------------------------
    tensor_container() : _size(0), _data(0) {}

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Contructor when given an array with the data for the container
    /// @param[in]  data    The data to use to initalize the container data with
    // ------------------------------------------------------------------------------------------------------
    tensor_container(container_type& data)
    : _size(data.size()), _data(data){}
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the size (total number of elements) in the container
    /// @return     The size of the container
    // ------------------------------------------------------------------------------------------------------
    size_t size() const { return _size; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets an element from the container
    /// @param[in]  i   The index of the element in the container
    /// @return     A reference to the element at the index i in the container
    // ------------------------------------------------------------------------------------------------------  
    inline T& operator[](size_t i) { return _data[i]; }
private:
    container_type  _data;                                          //!< Dynamic data container for a tensor
    size_t          _size;                                          //!< Number of elements in the container
};

}               // End namespace ftl

#endif          // FTL_TENSOR_CONTAINER_HPP
