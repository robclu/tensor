// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor specialization with a dynamic container using the cpu.
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
 *  with Tensor; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * ----------------------------------------------------------------------------------------------------------
 */ 

#ifndef FTL_TENSOR_DYNAMIC_CPU_HPP
#define FTL_TENSOR_DYNAMIC_CPU_HPP

#include "mapper.hpp"
#include "tensor_expression_dynamic_cpu.hpp"        // NOTE: Only including expression specialization for 
                                                    //       dynamic cpu implementation -- all specializations
                                                    //       are provided by tensor_expressions.hpp 

#include <initializer_list>
#include <numeric>

// NOTE : Using long template names results in extremely bulky code, so the following abbreviations are
//        used to reduve the bulk for template parameters:
//          - DT    = Dtype         = data type
//          - SF    = SizeFirst     = size of first dimension
//          - SR    = SizeRest      = size of other dimensions
//          - CPU   = CPU           = CPU device used for computation
namespace ftl {

// Forward declaration of TensorInterface so that we can provide the specialization
template <typename Traits>
class TensorInterface;

// Type alias for dynamic cpu tensor to make the code more readable
template <typename DT>
using DynamicTensorCpu = TensorInterface<TensorTraits<DT, CPU>>;

// Specialization for a tensor using a dynamic container and CPU devices
template <typename DT>
class TensorInterface<TensorTraits<DT, CPU>> : public TensorExpression<DynamicTensorCpu<DT> , 
                                                                       TensorTraits<DT, CPU>> {   
public:
    // ---------------------------------------- ALIAS'S ----------------------------------------------------- 
    using traits            = TensorTraits<DT, CPU>;
    using container_type    = typename traits::container_type;
    using data_container    = typename traits::data_container;
    using dim_container     = typename traits::dim_container;
    using data_type         = typename traits::data_type;
    using size_type         = typename traits::size_type;
    // ------------------------------------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Default constructor - sets the data to have no elements, the rank to the specified rank
    // ------------------------------------------------------------------------------------------------------
    explicit TensorInterface(size_type rank) : _data(0), _rank(rank), _dim_sizes(rank) {}

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Constructor using vectors to set the dimension sizes and the data of the tensor. Moves the 
    ///             data if the data are passed as rvalue references.
    /// @param      dim_sizes    The sizes of each of the dimensions for the tensor.
    /// @param      data         The data for the tensor.
    // ------------------------------------------------------------------------------------------------------
    TensorInterface(dim_container& dim_sizes, data_container& data);
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Constructor using vectors to set the dimension sizes and the data of the tensor. Moves the 
    ///             data if the data are passed as rvalue references.
    /// @param      dim_sizes    The sizes of each of the dimensions for the tensor.
    /// @param      data         The data for the tensor.
    // ------------------------------------------------------------------------------------------------------
    TensorInterface(dim_container&& dim_sizes, data_container&& data);
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Constructor using an initializer list - sets the size of each of the dimensions to the 
    ///             values in the intializer_list and the total number of elements equal to the product of 
    ///             the dimension sizes. 
    /// @param[in]  dim_sizes    The list of dimension sizes where the nth element in the list sets the size 
    ///             of the nth dimension of the tensor.
    // ------------------------------------------------------------------------------------------------------
    TensorInterface(std::initializer_list<size_type> dim_sizes); 
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Constructor for creation from a tensor expression -- this is only used for simple 
    ///             expressions (which do not modify the rank and/or dimension sizes) -- such as addition
    ///             and subtraction. Rank modifying expressions-- such as multiplication and slicing -- have 
    ///             specialized constructors (to be implemented).
    /// @param[in]  expression      The expression instance to create the static tensor from
    /// @tparam     Expression      The type of the expressionA
    /// @tparam     Traits          The tensor traits of the expression
    // ------------------------------------------------------------------------------------------------------
    template <typename Expression, typename Traits>
    TensorInterface(const TensorExpression<Expression, Traits>& expression);
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Gets the rank (number of dimensions) of the tensor.
    /// @return    The rank (number of dimensions) of the tensor.
    // ------------------------------------------------------------------------------------------------------
    inline size_type rank() const { return _rank; }    
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Gets the size (total number of elements) of the tensor
    /// @return    The total number of elements in the tensor.
    // ------------------------------------------------------------------------------------------------------
    inline size_type size() const { return _data.size(); }
   
    // NOTE: need to add out of range exception here too 
    // ------------------------------------------------------------------------------------------------------
    /// @brief     Gets the size of a specific dimension of the tensor, if the requested dimension is 
    ///            invalid then 0 is returned.
    /// @param[in] dim                 The dimension for which the size must be returned.
    /// @return    The number of elements in the requested dimension, if the dimension is a valid dimension
    ///            for the tensor, otherwise 0 is returned.
    // ------------------------------------------------------------------------------------------------------
    inline size_t size(const int dim) const { return dim < _rank ? _dim_sizes[dim] : 0; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets a vector holding the size of each dimension of the tensor.
    /// @return     A vector holding the size of each dimension of the tensor.
    // ------------------------------------------------------------------------------------------------------
    const dim_container& dim_sizes() const { return _dim_sizes; }
     
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the tensor data.
    /// @return     The data for the tensor.
    // ------------------------------------------------------------------------------------------------------
    const data_container& data() const { return _data; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Initializes each element of the tensor between a range using a uniform ditribution
    /// @param[in]  min     The minimum value of an element after the initialization
    /// @param[in]  max     The max value of an element after the initialization
    // ------------------------------------------------------------------------------------------------------
    void initialize(const data_type min, const data_type max);

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the element at position i in the tensor's data vector, by refernce
    /// @param[in]  i   The index of the element to access.
    /// @return     The element at position i in the tensor's data vecor.
    // ------------------------------------------------------------------------------------------------------
    inline data_type& operator[](size_type i) { return _data[i]; }

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the element at position i in the tensor's data vector, by value.
    /// @param[in]  i   The index of the element to access.
    /// @return     The element at position i in the tensor's data vector.
    // ------------------------------------------------------------------------------------------------------
    inline const data_type& operator[](size_type i) const { return _data[i]; }

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the element at a given index for each dimension of a tensor -- there is no bound
    ///             checking as bound checking implementations will be provided through .at()
    /// @param[in]  index_dim_one   The index of the element in dimension 1
    /// @param[in]  index_dim_other The index of the element in the other dimensions
    /// @tparam     IF              The type of the first index parameter
    /// @tparam     IR              The types of the rest of the index parameters
    /// @return     A reference to the element at the position given by the indices
    // ------------------------------------------------------------------------------------------------------
    template <typename IF, typename... IR>
    DT& operator()(IF index_dim_one, IR... index_dim_other);
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the element at a given index for each dimension of a tensor -- there is no bound
    ///             checking as bound checking implementations will be provided through .at()
    /// @param[in]  index_dim_one   The index of the element in dimension 1
    /// @param[in]  index_dim_other The index of the element in the other dimensions
    /// @tparam     IF              The type of the first index parameter
    /// @tparam     IR              The types of the rest of the index parameters
    /// @return     The value of the element at the position given by the indices
    // ------------------------------------------------------------------------------------------------------
    template <typename IF, typename... IR>
    DT operator()(IF index_dim_one, IR... index_dim_other) const; 
private:
    data_container      _data;              //!< Data for the tensor
    dim_container       _dim_sizes;         //!< Sizes of the dimensions for the tensor
    size_type           _rank;              //!< The rank (number of dimensions) in the tensor
};

// ------------------------------------------- IMPLEMENTATIONS ----------------------------------------------

// ----------------------------------------------- PUBLIC ---------------------------------------------------

template <typename DT>
TensorInterface<TensorTraits<DT, CPU>>::TensorInterface(std::initializer_list<size_type> dim_sizes)
: _data(std::accumulate(dim_sizes.begin(), dim_sizes.end(), 1, std::multiplies<size_type>())), 
  _rank(dim_sizes.size())
{   
    for (auto& element : dim_sizes) _dim_sizes.push_back(element);
}

template <typename DT>
TensorInterface<TensorTraits<DT, CPU>>::TensorInterface(dim_container& dim_sizes, data_container& data)
: _data(data), _rank(dim_sizes.size()), _dim_sizes(dim_sizes)
{
    // TODO: Add exception checking that the number of elements in the data container is the same as the
    //       product of the sizes of the dimensions that were given
    
}

template <typename DT>
TensorInterface<TensorTraits<DT, CPU>>::TensorInterface(dim_container&& dim_sizes, data_container&& data)
: _data(data), _rank(dim_sizes.size()), _dim_sizes(dim_sizes)
{
    // TODO: Add exception checking that the number of elements in the data container is the same as the
    //       product of the sizes of the dimensions that were given
    
}
  
template <typename DT> template <typename E, typename T> 
TensorInterface<TensorTraits<DT, CPU>>::TensorInterface(const TensorExpression<E, T>& expression)
: _data(expression.size()), _dim_sizes(expression.dim_sizes()), _rank(expression.rank())
{
    for (size_type i = 0; i != size(); ++i) _data[i] = expression[i];
}

template <typename DT>
void TensorInterface<TensorTraits<DT, CPU>>::initialize(const data_type min, const data_type max)
{
    std::random_device                  rand_device;
    std::mt19937                        gen(rand_device());
    std::uniform_real_distribution<>    dist(min, max);
    for (auto& element : _data) element = static_cast<data_type>(dist(gen));     
}

template <typename DT> template <typename IF, typename... IR>
DT& TensorInterface<TensorTraits<DT, CPU>>::operator()(IF dim_one_index, IR... other_dim_indices) 
{
    return _data[DynamicMapper::indices_to_index(_dim_sizes, dim_one_index, other_dim_indices...)];
}

template <typename DT> template <typename IF, typename... IR>
DT TensorInterface<TensorTraits<DT, CPU>>::operator()(IF dim_one_index, IR... other_dim_indices) const
{
    return _data[DynamicMapper::indices_to_index(_dim_sizes, dim_one_index, other_dim_indices...)];
}

}               // End namespace ftl
#endif          // FTL_TENSOR_DYNAMIC_CPU_HPP
