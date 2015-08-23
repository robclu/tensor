// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor library tensor class
// ----------------------------------------------------------------------------------------------------------

/*
 * ----------------------------------------------------------------------------------------------------------
 *  Header file for tensor tensor class
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

#ifndef FTL_TENSOR_HPP
#define FTL_TENSOR_HPP

#include "index_mapper.hpp"
#include "tensor_expressions.hpp"
#include "utils.hpp"

#include <initializer_list>
#include <numeric>

namespace ftl {
    
// ----------------------------------------------------------------------------------------------------------
/// @class  tensor
/// @brief  Allows an N dimensional space to be created to store data and operate on the data.               \n
///                                                                                                          \n
///         The first dimension of the tensor is 'accross' or the number of columns, so that the first       \n 
///         dimension is arranged as it it in memory so a 2D tensor with dimensions [3,2] will have 3        \n
///         and 2 rows.                                                                                      \n
///                                                                                                          \n
///         Detailed usage of the tensor class can be found in the unit tests for the class.                 \n
///         The basic usage is:                                                                              \n
///                                                                                                          \n
///         tensor<int, 3> tensor = {2, 2, 2}           // Create a 3-dimensional (rank 3) tensor            \n
///                                                                                                          \n
///         The above tensor is of int type and each dimension has a size of 2, thus the tensor is a         \n
///         matrix with 2 pages. Operations can be performed such as:                                        \n
///                                                                                                          \n
///         tensor<int, 3> new_tensor = tensor + tensor + tensor    // Add 3 tensors                         \n
///         tensor<int, 2> slice_tensor = tensor(j,i)               // New tensor from dim 1 and 2 of old 
///                                                                    tensor                                \n
/// @tparam T   Type of data used by the tensor.
/// @tparam R   Rank of the tensor (the number of dimensions it has).
// ----------------------------------------------------------------------------------------------------------
template <typename T, size_t R>
class tensor : public tensor_expression<T, tensor<T, R>> {
public:
    using typename tensor_expression<T, tensor<T, R>>::container_type;
    using typename tensor_expression<T, tensor<T, R>>::size_type;
    using typename tensor_expression<T, tensor<T, R>>::value_type;
    using typename tensor_expression<T, tensor<T, R>>::reference;
private:
    container_type          _data;                          ///< Container to hold tensor data elements
    std::vector<size_type>  _dim_sizes;                     ///< Sizes of each of the tensor's dimensions
public:
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Default constructor - sets the member variables to 0, and the number of dimensions equal 
    ///            to the rank.
    // ------------------------------------------------------------------------------------------------------
    tensor() : _data(0), _dim_sizes(R) {}
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Constructor using vectors to set the dimension sizes and the data of the tensor.
    /// @param     dim_sizes    The sizes of each of the dimensions for the tensor.
    /// @param     data         The data for the tensor.
    // ------------------------------------------------------------------------------------------------------
    tensor(std::vector<size_type>& dim_sizes, container_type& data);
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Constructor using an initializer list - sets the size of each of the dimensions to the 
    ///            values in the intializer_list and the total number of elements equal to the product of 
    ///            the dimension sizes.
    /// @param[in] dim_sizes    The list of dimension sizes where the nth element in the list sets the size 
    ///            of the nth dimension of the tensor.
    // ------------------------------------------------------------------------------------------------------
    tensor(std::initializer_list<int> dim_sizes) 
    : _data(std::accumulate(dim_sizes.begin(), dim_sizes.end(), 1, std::multiplies<int>()))
    {   
        ASSERT(dim_sizes.size(), ==, R); 
        for (auto& element : dim_sizes) _dim_sizes.push_back(element);
    } 
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Constructor using a tensor_expression - sets the data of the tensor to the data of the
    ///            tensor_expression so that tensors can be created from the ouputs of operations such as 
    ///            addition and subtraction.
    /// @param[in] expression  The expression which must be used to construct the tensor.
    /// @tparam    E           The type of the expression.
    // ------------------------------------------------------------------------------------------------------
    template <typename E>
    tensor(tensor_expression<T,E> const& expression) 
    : _dim_sizes(expression.dim_sizes())
    {
        E const& expr = expression;
        _data.resize(expr.size());
        for (size_type i = 0; i != expr.size(); ++i) {
            _data[i] = expr[i];
        }
    }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Gets the size (total number of elements) of the tensor
    /// @return    The total number of elements in the tensor.
    // ------------------------------------------------------------------------------------------------------
    size_type size() const { return _data.size(); }

    // ------------------------------------------------------------------------------------------------------
    /// @brief     Gets the size of a specific dimension of the tensor, if the requested dimension is 
    ///            invalid then 0 is returned.
    /// @param[in] dim                 The dimension for which the size must be returned.
    /// @return    The number of elements in the requested dimension, if the dimension is a valid dimension
    ///            for the tensor, otherwise 0 is returned.
    /// @throw     TesnorOutOfRange    Throws an error if the requested dimension is invalid for the tensor.
    // ------------------------------------------------------------------------------------------------------
    size_t size(const int dim) const;
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Gets the rank (number of dimensions) of the tensor.
    /// @return    The rank (number of dimensions) of the tensor.
    // ------------------------------------------------------------------------------------------------------
    size_type rank() const { return R; }

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets a vector holding the size of each dimension of the tensor.
    /// @return     A vector holding the size of each dimension of the tensor.
    // ------------------------------------------------------------------------------------------------------
    const std::vector<size_type>& dim_sizes() const { return _dim_sizes; }
     
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the tensor data.
    /// @return     The data for the tensor.
    // ------------------------------------------------------------------------------------------------------
    const container_type& data() const { return _data; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the element at position i in the tensor's data vector, by reference.
    /// @param[in]  i   The index of the element to access.
    /// @return     The element at position i in the tensor's data vecor.
    // ------------------------------------------------------------------------------------------------------
    reference operator[](size_type i) { return _data[i]; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the element at position i in the tensor's data vector, by value.
    /// @param[in]  i   The index of the element to access.
    /// @return     The element at position i in the tensor's data vector.
    // ------------------------------------------------------------------------------------------------------
    value_type operator[](size_type i) const { return _data[i]; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      General case for the calculation of the offset for setting an element of the Tensor. 
    /// @param[in]  idx     The index of the element in the current dimension used in the calculation.
    /// @param[in]  indices The indices of the element in the remaining dimensions to use for the 
    ///             calculation.
    /// @tparam     Mapper  The functor to use for the mapping. Generally this will be the defualt index
    ///             mapper, but using the 'functor' allows for more dlexibility
    /// @tparam     I       The type of the idx parameter.
    /// @tparam     Is      The types of the remaining index parameters.
    /// @return     The element at the specified position, if valid.
    /// @throw      tensor_invalid_arguments    If the number of arguments does not match the rank of the
    ///             tensor then an error is thrown and the function returns the first value in the tensor
    // ------------------------------------------------------------------------------------------------------
    template <typename Mapper = index_mapper, typename I = int, typename... Is>
    typename std::enable_if<std::is_arithmetic<I>::value, T&>::type operator()(I idx, Is... indices) 
    {
        // Since this is variadic, we need to check that the number 
        // of indices specified matches the rank of the tensor
        try {                                            
            if (sizeof...(Is) + 1 != R) 
                throw tensor_invalid_arguments(sizeof...(Is) + 1, R);
        } catch (tensor_invalid_arguments& e) {
            std::cerr << e.what() << std::endl;
            return _data[0];
        }  
        
        // Create index mapper;
        Mapper mapper;
        
        // Return result 
        return _data[mapper(_dim_sizes, idx, indices...)];
    }
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief      General case for the calculation of the offset for getting an element of the Tensor. 
    /// @param[in]  idx     The index of the element in the current dimension used in the calculation.
    /// @param[in]  indices The indices of the element in the remaining dimensions to use for the 
    ///             calculation.
    /// @tparam     Mapper  The functor to use for the mapping. Generally this will be the defualt index
    ///             mapper, but using the 'functor' allows for more dlexibility
    /// @tparam     I       The type of the idx parameter.
    /// @tparam     Is      The types of the remaining index parameters.
    /// @return     The element at the specified position, if valid.
    /// @throw      tensor_invalid_arguments    If the number of arguments does not match the rank of the
    ///             tensor then an error is thrown and the function returns the first value in the tensor
    // ------------------------------------------------------------------------------------------------------
    template <typename Mapper = index_mapper, typename I, typename... Is>
    typename std::enable_if<std::is_arithmetic<I>::value, const T&>::type 
    operator()(I idx, Is... indices) const
    {
        // Since this is variadic, we need to check that the number 
        // of indices specified matches the rank of the tensor
        try {                                            
            if (sizeof...(Is) + 1 != R) 
                throw tensor_invalid_arguments(sizeof...(Is) + 1, R);
        } catch (tensor_invalid_arguments& e) {
            std::cerr << e.what() << std::endl;
            return _data[0];
        }  
        
        // Create index mapper;
        Mapper mapper;
        
        // Return result 
        return _data[mapper(_dim_sizes, idx, indices...)]; 
    }

};

// -------------------------------------- IMPLEMENTATIONS ---------------------------------------------------

// ------------------------------------------ PUBLIC --------------------------------------------------------

template <typename T, size_t R> 
tensor<T, R>::tensor(std::vector<size_type>& dim_sizes, container_type& data)
: _dim_sizes(std::move(dim_sizes)), _data(std::move(data)) 
{
    ASSERT(_dim_sizes.size(), ==, R);               // Check number of dimensions is equal to the rank
    ASSERT(_data.size(), ==,                        // Check total data size is consistent with dim sizes
           std::accumulate(_dim_sizes.begin()           , 
                           _dim_sizes.end()             , 
                           1                            , 
                           std::multiplies<size_type>() ));
}

template <typename T, size_t R>
size_t tensor<T, R>::size(const int dim) const
{
    try {
        if (dim >= R) throw tensor_out_of_range(dim, R);
        return _dim_sizes[dim];
    } catch (tensor_out_of_range& e) {
        std::cout << e.what() << std::endl;
         return 0;
    }
}

// ---------------------------------------- PRIVATE ---------------------------------------------------------

}           // End namespace ftl

#endif      // FTL_TENSOR_HPP  
