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
    
// --------------------------- FORWARD DECLARATIONS AND FRIEND FUNCTIONS ------------------------------------

template <typename T, size_t SF, size_t...SR>
class static_tensor;

// ----------------------------------------------------------------------------------------------------------
/// @brief      Initializes a static tensor with values between the given range
/// @param[in]  stat_tensor     A pointer to the static tensor to initialize
/// @param[in]  min             The minimum value to initialize the tensor with
/// @param[in]  max             The maximum value to initialize the tensor with
// ----------------------------------------------------------------------------------------------------------
template <typename T, size_t SF, size_t...SR>
void initialize(static_tensor<T, SF, SR...>& stat_tensor, const T min, const T max);

// ----------------------------------------------------------------------------------------------------------

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
    using data_type         = T;
    using container_type    = tensor_container<T, SF, SR...>;
    using data_container    = typename container_type::data_container;
    using dim_container     = typename nano::runtime_converter<
                                                typename container_type::dimension_sizes>::array_type;
    // ------------------------------------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Default constructor, converts the compile time list of dimension sizes to an array
    // ------------------------------------------------------------------------------------------------------
    static_tensor();
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Constructor for when the data is given as an lvalue 
    /// @param[in]  data    The data to use for the tensor
    // ------------------------------------------------------------------------------------------------------
    static_tensor(data_container& data);
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Constructor for when the data is specified as a literal list
    /// @param[in]  first_value     The first value in the literal list
    /// @param[in]  other_values    The rest of the values in the literal list
    /// @tparam     TF              The type of the first value
    /// @tparam     TR              The type of the rest of the values
    // ------------------------------------------------------------------------------------------------------
    template <typename TF, typename... TR> 
    static_tensor(TF&& first_value, TR&&... other_values);

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Constructor for when a static tensor is created from a tensor expression -- this is only 
    ///             used for simple expression (which do not modify the rank and dimension sizes) -- such as
    ///             addition and subtraction. Rank modifying expressions have specialized constructors
    /// @param[in]  expression      The expression to create the static tensor from
    /// @tparam     E               The type of the expression
    // ------------------------------------------------------------------------------------------------------
    template <typename E>
    static_tensor(const tensor_expression<T, E>& expression);
    
    //
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
    constexpr const dim_container& dim_sizes() const { return _dim_sizes; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets an element from the tensor
    /// @param[in]  i   The index of the element in the tensor
    /// @return     A reference to the element at the index i in the tensor
    // ------------------------------------------------------------------------------------------------------
    inline data_type& operator[](size_t i) { return _data[i]; }
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets an element from the tensor
    /// @param[in]  i   The index of the element in the tensor
    /// @return     The value of the element at the index i in the tensor
    // ------------------------------------------------------------------------------------------------------
    inline data_type operator[](size_t i) const { return _data[i]; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the element at a given index for each dimension of a tensor -- there is no bound
    ///             checking as bound checking implementations will be provided through .at()
    /// @param[in]  index_dim_one   The index of the element in dimension 1
    /// @param[in]  index_dim_other The index of the element in the other dimensions
    /// @tparam     Mapper          The functor used to determine the mapping 
    /// @tparam     IF              The type of the first index parameter
    /// @tparam     IR              The types of the rest of the index parameters
    /// @return     A reference to the element at the position given by the indices
    // ------------------------------------------------------------------------------------------------------
    template <typename Mapper = mapper, typename IF, typename... IR>
    data_type& operator()(IF index_dim_one, IR... index_dim_other);
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the element at a given index for each dimension of a tensor -- there is no bound
    ///             checking as bound checking implementations will be provided through .at()
    /// @param[in]  index_dim_one   The index of the element in dimension 1
    /// @param[in]  index_dim_other The index of the element in the other dimensions
    /// @tparam     Mapper          The functor used to determine the mapping 
    /// @tparam     IF              The type of the first index parameter
    /// @tparam     IR              The types of the rest of the index parameters
    /// @return     The value of the element at the position given by the indices
    // ------------------------------------------------------------------------------------------------------
    template <typename Mapper = mapper, typename IF, typename... IR>
    data_type operator()(IF index_dim_one, IR... index_dim_other) const;
    
    friend void initialize<T, SF, SR...>(static_tensor& stat_tensor, const T min, const T max);
private:
    container_type      _data;                  //!< The data container which holds all the data
    dim_container       _dim_sizes;             //!< The sizes of the dimensions for the tensor
};

// ----------------------------------------------- IMPLEMENTATIONS ------------------------------------------

// ------------------------------------------------- PUBLIC -------------------------------------------------

template <typename T, size_t SF, size_t...SR> 
static_tensor<T, SF, SR...>::static_tensor() 
{
    // Convert the nano::list of dimension sizes to a constant array
     _dim_sizes = nano::runtime_converter<typename container_type::dimension_sizes>::to_array(); 
};

template <typename T, size_t SF, size_t...SR> 
static_tensor<T, SF, SR...>::static_tensor(data_container& data)
: _data(data) 
{
    // Convert the nano::list of dimension sizes to a constant array
    _dim_sizes = nano::runtime_converter<typename container_type::dimension_sizes>::to_array();
}

template <typename T, size_t SF, size_t...SR> template <typename TF, typename... TR> 
static_tensor<T, SF, SR...>::static_tensor(TF&& first_value, TR&&... other_values) 
: _data(std::forward<TF>(first_value), std::forward<TR>(other_values)...) 
{
    // Convert the nano::list of dimension sizes to a constant array
    _dim_sizes = nano::runtime_converter<typename container_type::dimension_sizes>::to_array(); 
}

template <typename T, size_t SF, size_t...SR> template <typename E> 
static_tensor<T, SF, SR...>::static_tensor(const tensor_expression<T, E>& expression) 
{   
    // Convert the nano::list of dimension sizes to a constant array
    _dim_sizes = nano::runtime_converter<typename container_type::dimension_sizes>::to_array();  
    assert(_dim_sizes.size() == expression.dim_sizes().size());     
    for (size_t i = 0; i != size(); ++i) _data[i] = expression[i];
}

template <typename T, size_t SF, size_t...SR> template <typename Mapper, typename IF, typename... IR>
T& static_tensor<T, SF, SR...>::operator()(IF dim_one_index, IR... other_dim_indices) 
{
    using dimension_sizes = typename container_type::dimension_sizes;
    return _data[static_mapper::indices_to_index<dimension_sizes>(dim_one_index, other_dim_indices...)];
}

template <typename T, size_t SF, size_t...SR> template <typename Mapper, typename IF, typename... IR>
T static_tensor<T, SF, SR...>::operator()(IF dim_one_index, IR... other_dim_indices) const
{
    using dimension_sizes = typename container_type::dimension_sizes;
    return _data[static_mapper::indices_to_index<dimension_sizes>(dim_one_index, other_dim_indices...)];
}

// ----------------------------------------------- FRIENDS --------------------------------------------------

template <typename T, size_t SF, size_t...SR>
void initialize(static_tensor<T, SF, SR...>& stat_tensor, const T min, const T max)
{   
    using data_type = typename static_tensor<T, SF, SR...>::data_type;
    std::random_device                  rand_device;
    std::mt19937                        gen(rand_device());
    std::uniform_real_distribution<>    dist(min, max);
    for (auto& element : stat_tensor._data) element = static_cast<data_type>(dist(gen));        
}

// ------------------------------------------------- ALIAS'S ------------------------------------------------

template <typename T, size_t SF, size_t... SR>
using stensor = static_tensor<T, SF, SR...>;

}           // End namespace ftl

#endif      // FTL_STATIC_TENSOR_HPP
