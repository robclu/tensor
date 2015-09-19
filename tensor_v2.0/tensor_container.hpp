// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for TensorConainer class to allow both static and dynamic containers
// ----------------------------------------------------------------------------------------------------------

/*
* ----------------------------------------------------------------------------------------------------------
*  Tensor program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published
*  by the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  Tensor is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License along
*  with tensor; if not, write to the Free Software Foundation,
*  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
* ----------------------------------------------------------------------------------------------------------
*/

#ifndef FTL_TENSOR_CONTAINER_HPP
#define FTL_TENSOR_CONTAINER_HPP

#include <nano/nano.hpp>

#include <array>
#include <vector>

namespace ftl {
   
// ----------------------------------------------------------------------------------------------------------
/// @struct     TensorContainer
/// @brief      Container for tensor data depending on if the tensor is static (dimension sizes, and hence the
///             total number of elements, are known at compile time -- uses std::array) or dynamic (dimension 
///             sizes are not known at compile time -- uses std::vector).
/// @tparam     Dtype   The type of data used by the tensor
/// @tparam     Sizes   The sizes of the dimensions (optional)
// ----------------------------------------------------------------------------------------------------------
template <typename Dtype, size_t... Sizes>
class TensorContainer;

// Specialize for static containers
template <typename Dtype, size_t SizeFirst, size_t... SizeRest>
class TensorContainer<Dtype, SizeFirst, SizeRest...> {
public:
    // ---------------------------------------- ALIAS'S -----------------------------------------------------
    using data_type         = Dtype;
    using dimension_sizes   = nano::list<nano::size_t<SizeFirst>, nano::size_t<SizeRest>...>;
    using dimension_product = nano::multiplies<dimension_sizes>;
    using data_container    = std::array<data_type, dimension_product::result>; 
    using size_type         = typename data_container::size_type;
    using iterator          = typename data_container::iterator;
    // ------------------------------------------------------------------------------------------------------

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Default constructor 
    // ------------------------------------------------------------------------------------------------------
    TensorContainer() {}

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Contructor when given an array with the data for the container
    /// @param[in]  data    The data to use to initalize the container data with
    // ------------------------------------------------------------------------------------------------------
    constexpr TensorContainer(data_container& data)
    : _data(data) {}

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Move constructor for when the data is given as a literal list
    /// @param[in]  first_value     The first value in the literal list 
    /// @param[in]  other_valeus    The rest of the values in the literal list
    /// @tparam     TF              The type of the first_value parameter
    /// @tparam     TR              The type of the rest of the parameters
    // ------------------------------------------------------------------------------------------------------
    template <typename TF, typename... TR> 
    constexpr TensorContainer(TF&& first_value, TR&&... other_values) 
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
    inline data_type& operator[](size_t i) { return _data[i]; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Returns an iterator to the first element of the container
    /// @return     An iterator to the first element of the container
    // ------------------------------------------------------------------------------------------------------
    iterator begin() { return _data.begin(); }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Returns an iterator to the element following the last element
    /// @return     An iterator to the element following the last element
    // ------------------------------------------------------------------------------------------------------
    iterator end() { return _data.end(); }
private:
    data_container _data;                                                   //!< Static data for a tensor
};

// Specialization for dynamic container which the dimension sizes
// (and hence the number of elements) are not known at compile time
template <typename Dtype>
class TensorContainer<Dtype> {
public:
    // ----------------------------------------- ALIAS'S ----------------------------------------------------
    using data_type         = Dtype;
    using data_container    = std::vector<data_type>;
    using size_type         = typename data_container::size_type;
    using iterator          = typename data_container::iterator;
    // ------------------------------------------------------------------------------------------------------
 
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Default constructor 
    // ------------------------------------------------------------------------------------------------------
    TensorContainer() : _size(0), _data(0) {}

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Contructor when given an array with the data for the container
    /// @param[in]  data    The data to use to initalize the container data with
    // ------------------------------------------------------------------------------------------------------
    TensorContainer(data_container& data)
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
    inline data_type& operator[](size_t i) { return _data[i]; }
private:
    data_container  _data;                                          //!< Dynamic data container for a tensor
    size_t          _size;                                          //!< Number of elements in the container
};

}               // End namespace ftl

#endif          // FTL_TENSOR_CONTAINER_HPP
