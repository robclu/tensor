// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor specialization with a static container using the cpu.
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

#ifndef FTL_TENSOR_STATIC_CPU_HPP
#define FTL_TENSOR_STATIC_CPU_HPP

#include "mapper.hpp"
#include "tensor_expression_static_cpu.hpp"         // NOTE: Only including expression specialization for 
                                                    //       static cpu implementation -- all specializations
                                                    //       are provided by tensor_expressions.hpp 

// NOTE : Using long template names results in extremely bulky code, so the following abbreviations are
//        used to reduve the bulk for template parameters:
//          - DT = Dtype        = data type
//          - SF = SizeFirst    = size of first dimension
//          - SR = SizeRest     = size of other dimensions
namespace ftl {

// Forward declaration of TensorInterface so that we can provide the specialization
template <typename Traits>
class TensorInterface;

// Type alias for static cpu tensor to make the code more readable
template <typename DT, size_t SF, size_t... SR>
using StaticTensorCpu = TensorInterface<TensorTraits<DT, CPU, SF, SR...>>;

// Specialization for a tensor using a static container and a CPU device
template <typename DT, size_t SF, size_t... SR>
class TensorInterface<TensorTraits<DT, CPU, SF, SR...>> : public TensorExpression<
                                                                    StaticTensorCpu<DT, SF, SR...>  , 
                                                                    TensorTraits<DT, CPU, SF, SR...>> {   
public:
    // ---------------------------------------- ALIAS'S ----------------------------------------------------- 
    using traits            = TensorTraits<DT, CPU, SF, SR...>;
    using size_type         = typename traits::size_type;
    using data_type         = typename traits::data_type;
    using container_type    = typename traits::container_type;
    using data_container    = typename container_type::data_container;    
    using dim_container     = typename container_type::dim_container;    
    // ------------------------------------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Default constructor, converts the compile time list of dimension sizes to an array
    // ------------------------------------------------------------------------------------------------------
    TensorInterface();
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Constructor for when the data is given as an lvalue 
    /// @param[in]  data    The data to use for the tensor
    // ------------------------------------------------------------------------------------------------------
    TensorInterface(data_container& data);
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Constructor for when the data is specified as a literal list
    /// @param[in]  first_value     The first value in the literal list
    /// @param[in]  other_values    The rest of the values in the literal list
    /// @tparam     TF              The type of the first value
    /// @tparam     TR              The type of the rest of the values
    // ------------------------------------------------------------------------------------------------------
    template <typename TF, typename... TR> 
    TensorInterface(TF&& first_value, TR&&... other_values);

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Constructor for creation from a tensor expression -- this is only used for simple 
    ///             expressions (which do not modify the rank and/or dimension sizes) -- such as addition
    ///             and subtraction. Rank modifying expressions-- such as multiplication and slicing -- have 
    ///             specialized constructors (to be implemented).
    /// @param[in]  expression      The expression instance to create the static tensor from
    /// @tparam     Expression      The type of the expression
    // ------------------------------------------------------------------------------------------------------
    template <typename Expression, typename Traits>
    TensorInterface(const TensorExpression<Expression, Traits>& expression);
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the rank (number of dimensions) of the tensor
    /// @return     The rank (number of dimensions) of the tensor
    // ------------------------------------------------------------------------------------------------------
    constexpr size_type rank() const { return sizeof...(SR) + 1; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the size (total number of elements) in the tensor
    /// @return     The size of the tensor
    // ------------------------------------------------------------------------------------------------------
    constexpr size_type size() const { return _data.size(); }
 
    // TODO: Add out of range exception
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets the size (total number of elements) in a specific dimension of the tensor, if the
    ///             dimension is valid
    /// @param[in]  dim     The dimension to get the size of
    /// @return     The size of the requested dimension of the tensor if valid, otherwise 0
    // ------------------------------------------------------------------------------------------------------
    inline size_type size(const size_type dim) const { return dim < rank() ? _dim_sizes[dim] : 0; }  
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets a reference to the container holding the sizes of the dimensions for the tensor
    /// @return     A constant reference to the dimension sizes of the tensor
    // ------------------------------------------------------------------------------------------------------
    constexpr const dim_container& dim_sizes() const { return _dim_sizes; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Initializes each element of the tensor between a range using a uniform ditribution
    /// @param[in]  min     The minimum value of an element after the initialization
    /// @param[in]  max     The max value of an element after the initialization
    // ------------------------------------------------------------------------------------------------------
    void initialize(const data_type min, const data_type max);
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets an element from the tensor
    /// @param[in]  i   The index of the element in the tensor
    /// @return     A reference to the element at the index i in the tensor
    // ------------------------------------------------------------------------------------------------------
    inline data_type& operator[](size_type i) { return _data[i]; }
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Gets an element from the tensor
    /// @param[in]  i   The index of the element in the tensor
    /// @return     The value of the element at the index i in the tensor
    // ------------------------------------------------------------------------------------------------------
    inline data_type operator[](size_type i) const { return _data[i]; }
   
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
    container_type      _data;                  //!< The data container which holds all the data
    dim_container       _dim_sizes;             //!< The sizes of the dimensions for the tensor
};

// ----------------------------------------------- IMPLEMENTATIONS ------------------------------------------

// ------------------------------------------------- PUBLIC -------------------------------------------------

template <typename DT, size_t SF, size_t...SR> 
TensorInterface<TensorTraits<DT, CPU, SF, SR...>>::TensorInterface() 
{
    // Convert the nano::list of dimension sizes to a constant array
     _dim_sizes = nano::runtime_converter<typename container_type::dimension_sizes>::to_array(); 
};

template <typename DT, size_t SF, size_t...SR> 
TensorInterface<TensorTraits<DT, CPU, SF, SR...>>::TensorInterface(data_container& data)
: _data(data) 
{
    // Convert the nano::list of dimension sizes to a constant array
    _dim_sizes = nano::runtime_converter<typename container_type::dimension_sizes>::to_array();
}

template <typename DT, size_t SF, size_t...SR> template <typename TF, typename... TR> 
TensorInterface<TensorTraits<DT, CPU, SF, SR...>>::TensorInterface(TF&& first_value, TR&&... other_values) 
: _data(std::forward<TF>(first_value), std::forward<TR>(other_values)...) 
{
    // Convert the nano::list of dimension sizes to a constant array
    _dim_sizes = nano::runtime_converter<typename container_type::dimension_sizes>::to_array(); 
}

template <typename DT, size_t SF, size_t...SR> template <typename E, typename T> 
TensorInterface<TensorTraits<DT, CPU, SF, SR...>>::TensorInterface(const TensorExpression<E, T>& expression) 
{   
    // Convert the nano::list of dimension sizes to a constant array
    _dim_sizes = nano::runtime_converter<typename container_type::dimension_sizes>::to_array();  
    assert(_dim_sizes.size() == expression.dim_sizes().size());     
    for (size_type i = 0; i != size(); ++i) _data[i] = expression[i];
}

template <typename DT, size_t SF, size_t... SR>
void TensorInterface<TensorTraits<DT, CPU, SF, SR...>>::initialize(const data_type min, const data_type max)
{
    std::random_device                  rand_device;
    std::mt19937                        gen(rand_device());
    std::uniform_real_distribution<>    dist(min, max);
    for (auto& element : _data) element = static_cast<data_type>(dist(gen));     
}

template <typename DT, size_t SF, size_t...SR> template <typename IF, typename... IR>
DT& TensorInterface<TensorTraits<DT, CPU, SF, SR...>>::operator()(IF dim_one_index, IR... other_dim_indices) 
{
    using dimension_sizes = typename container_type::dimension_sizes;
    return _data[StaticMapper::indices_to_index<dimension_sizes>(dim_one_index, other_dim_indices...)];
}

template <typename DT, size_t SF, size_t...SR> template <typename IF, typename... IR>
DT TensorInterface<TensorTraits<DT, CPU, SF, SR...>>::operator()(IF dim_one_index, IR... other_dim_indices) const
{
    using dimension_sizes = typename container_type::dimension_sizes;
    return _data[StaticMapper::indices_to_index<dimension_sizes>(dim_one_index, other_dim_indices...)];
}

}               // End namespace ftl
#endif          // FTL_TENSOR_STATIC_CPU_HPP
