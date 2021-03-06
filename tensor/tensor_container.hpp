// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for TensorConainer class to allow both static and dynamic containers
// ----------------------------------------------------------------------------------------------------------

/*
* ----------------------------------------------------------------------------------------------------------
*  Tensor is free software; you can redistribute it and/or modify
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

// Specialize for static containers -- for when the sizes of the dimensions are given at compile-time
template <typename Dtype, size_t SizeFirst, size_t... SizeRest>
class TensorContainer<Dtype, SizeFirst, SizeRest...> {
public:
    // ---------------------------------------- ALIAS'S -----------------------------------------------------
    using data_type         = Dtype;
    using dimension_sizes   = nano::list<nano::size_t<SizeFirst>, nano::size_t<SizeRest>...>;
    using dimension_product = nano::multiplies<dimension_sizes>;
    using data_container    = std::array<data_type, dimension_product::result>; 
    using dim_container     = typename nano::runtime_converter<dimension_sizes>::array_type;
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
    /// @param[in]  values          The first value in the literal list 
    /// @tparam     TR              The type of the rest of the parameters
    // ------------------------------------------------------------------------------------------------------
    template <typename... TR> 
    constexpr TensorContainer(TR&&... values) 
    : _data{{std::forward<TR>(values)...}} {}

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
    /// @brief      Gets an element from the container
    /// @param[in]  i   The index of the element in the container
    /// @return     A reference to the element at the index i in the container
    // ------------------------------------------------------------------------------------------------------
    inline const data_type& operator[](size_t i) const { return _data[i]; }
    
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
    using dim_container     = std::vector<size_type>;
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
    inline size_t size() const { return _size; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets an element from the container
    /// @param[in]  i   The index of the element in the container
    /// @return     A reference to the element at the index i in the container
    // ------------------------------------------------------------------------------------------------------  
    inline data_type& operator[](size_t i) { return _data[i]; }

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets an element from the container
    /// @param[in]  i   The index of the element in the container
    /// @return     A reference to the element at the index i in the container
    // ------------------------------------------------------------------------------------------------------  
    inline const data_type& operator[](size_t i) const { return _data[i]; }
    
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
    data_container  _data;                                          //!< Dynamic data container for a tensor
    size_t          _size;                                          //!< Number of elements in the container
};

}               // End namespace ftl

#endif          // FTL_TENSOR_CONTAINER_HPP
