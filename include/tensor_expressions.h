// ==========================================================================================================
//! @file   Header file for fastRNN tensor expression classes.
// ==========================================================================================================

/*
 * ==========================================================================================================
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
 * ==========================================================================================================
 */ 

#ifndef _FRNN_TENSOR_EXPRESSIONS_
#define _FRNN_TENSOR_EXPRESSIONS_

#include "tensor_utils.h"
#include "../containers/tuple.h"
#include "../containers/index_map.h"
#include "../util/errors.h"

#include <set>

namespace frnn {

// ==========================================================================================================
//! @class      TensorExpression 
//! @brief      Define a Tesnor expression, for example a Tensor itself, addition, subtraction ... which can
//!             then be used by operators to make operations on Tensors look mathematic.
//! @tparam     T   The type of data the expression uses
//! @tparam     E   The type of exprssion (Tensor, TensorAddition etc...)
// ==========================================================================================================
template <typename T, typename E>
class TensorExpression {
public:
    /* ============================================= Typedefs ============================================= */
    typedef std::vector<T>                      container_type;
    typedef typename container_type::size_type  size_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::reference  reference;
    /* ==================================================================================================== */
    
    // ======================================================================================================
    //! @brief     Returns the size of the expression
    //! @return    The size of the TensorExpression
    // ======================================================================================================
    size_type size() const { return static_cast<E const&>(*this).size(); }

    // ======================================================================================================
    //! @brief     Gets the sizes of the all the dimensions of the expression.
    //! @return    A constant reference to the dimension size vector of the expression 
    // ======================================================================================================
    const std::vector<size_type>& dimSizes() const { return static_cast<E const&>(*this).dimSizes(); }
    
    // ======================================================================================================
    //! @brief     Gets and element from the Tensor expression data.
    //! @param[in] i   The element in the expression which must be fetched.
    //! @return    The value of the element at position i of the expression data.
    // ======================================================================================================
    value_type operator[](size_type i) const { return static_cast<E const&>(*this)[i]; }

    // ======================================================================================================
    //! @brief     Gets a reference to the Tensor expression.
    //! @return    A reference to the Tensor expression E.
    // ======================================================================================================
    operator E&() { return static_cast<E&>(*this); }

    // ======================================================================================================
    //! @brief     Gets a constant reference to the Tensor expression.
    //! @return    A constant reference to the Tensror expression E.
    // ======================================================================================================
    operator E const&() const   { return static_cast<const  E&>(*this); }
};

// ==========================================================================================================
//! @class      TensorDifference
//! @brief      Expression class for calculating the difference of two tensors.
//! @tparam     T       The type of the data used by the tensors.
//! @tparam     E1      Expression to subtract from.
//! @tparam     E2      Expression to subtract with.
// ==========================================================================================================
template <typename T, typename E1, typename E2>
class TensorDifference : public TensorExpression<T, TensorDifference<T,E1,E2>> {
public:
    /* ====================================== Typedefs ==================================================== */
    using typename TensorExpression<T, TensorDifference<T,E1,E2>>::container_type;
    using typename TensorExpression<T, TensorDifference<T,E1,E2>>::size_type;
    using typename TensorExpression<T, TensorDifference<T,E1,E2>>::value_type;
    /* ==================================================================================================== */
private:
    E1 const& _x;       //!< First expression for subtraction
    E2 const& _y;       //!< Second expression for subtraction
public:
     // =====================================================================================================
     //! @brief         Constructs a TensorDifference class from the inputs.
     //! @tparam[in]    x   The first expression for subtraction
     //! @tparam[in]    y   The second expression for subtraction
     // =====================================================================================================
    TensorDifference(TensorExpression<T,E1> const& x, TensorExpression<T,E2> const& y) : _x(x), _y(y) 
    { 
        ASSERT(x.size(), ==, y.size());                         // Check total sizes
        for (int i = 0; i < x.dimSizes().size(); i++) {         // Check each dimension size
            ASSERT(x.dimSizes()[i], ==, y.dimSizes()[i]);
        }
    }
       
    // ======================================================================================================
    //! @brief     Gets the sizes of the all the dimensions of the expression.
    //! @return    A constant reference to the dimension size vector of the expression 
    // ======================================================================================================
    const std::vector<size_type>& dimSizes() const { return _x.dimSizes(); }
   
    // ======================================================================================================
    //! @brief     Returns the size of the expression
    //! @return    The size of the TensorExpression
    // ====================================================================================================== 
    size_type size() const { return _x.size(); }
   
    // ======================================================================================================
    //! @brief     Subtracts two elements (one from each Tensor) from the Tensor expression data.
    //! @param[in] i   The element in the expression which must be fetched.
    //! @return    The result of the subtraction of the Tensors.
    // ======================================================================================================
    value_type operator[](size_type i) const { return _x[i] - _y[i]; }
};      

// ==========================================================================================================
//! @class      TensorAddition
//! @brief      Expression class for calculating the addition of two tensors.
//! @tparam     T       Type of the data used by the tesors
//! @tparam     E1      Expression to add to.
//! @tparam     E2      Expression to add with.
// ==========================================================================================================
template <typename T, typename E1, typename E2>
class TensorAddition : public TensorExpression<T, TensorAddition<T,E1,E2>> {
public:
    /* ====================================== Typedefs ==================================================== */
    using typename TensorExpression<T, TensorAddition<T,E1,E2>>::container_type;
    using typename TensorExpression<T, TensorAddition<T,E1,E2>>::size_type;
    using typename TensorExpression<T, TensorAddition<T,E1,E2>>::value_type;
    /* ==================================================================================================== */
private:
    E1 const& _x;       //!< First expression for addition
    E2 const& _y;       //!< Second expression for addition
public:
     // =====================================================================================================
     //! @brief     Sets the expressions for addition and checks that they have the same ranks and dimension
     //!            sizes.
     //! @param[in] x       The first expression for addition.
     //! @param[in] y       The second expression for addition
     // =====================================================================================================
    TensorAddition(TensorExpression<T,E1> const& x, TensorExpression<T,E2> const& y) : _x(x), _y(y) 
    { 
        ASSERT(x.size(), ==, y.size());                         // Check total sizes
        for (int i = 0; i < x.dimSizes().size(); i++) {         // Check each dimension size
            ASSERT(x.dimSizes()[i], ==, y.dimSizes()[i]);
        }
    }
   
    // ======================================================================================================
    //! @brief     Gets the sizes of the all the dimensions of the expression.
    //! @return    A constant reference to the dimension size vector of the expression 
    // ======================================================================================================
    const std::vector<size_type>& dimSizes() const { return _x.dimSizes(); }
    
    // ======================================================================================================
    //! @brief     Returns the size of the expression.
    //! @return    The size of the TensorAddition.
    // ====================================================================================================== 
    size_type size() const { return _x.size(); }
    
    // ======================================================================================================
    //! @brief     Adds two elements (one from each Tensor) from the Tensor expression data.
    //! @param[in] i   The element in the expression which must be fetched.
    //! @return    The result of the subtraction of the Tensors.
    // ======================================================================================================
    value_type operator[](size_type i) const { return _x[i] + _y[i]; }
};      

// ==========================================================================================================
//! @class      TensorMultiplier
//! @brief      Expression class for creating an argument for a TensorMultiplication expression.
//! @tparam     T       Type of the data used by the Tensors.
//! @tparam     E1      Expression to multiply.
//! @tparam     I       The type of the variables used for the indices to multiply over.
// ==========================================================================================================
template <typename T, typename E1, typename I>
class TensorMultiplier : public TensorExpression<T, TensorMultiplier<T, E1, I>> {
public:
    /* ====================================== Typedefs ==================================================== */
    using typename TensorExpression<T, TensorMultiplier<T, E1, I>>::container_type;
    using typename TensorExpression<T, TensorMultiplier<T, E1, I>>::size_type;
    using typename TensorExpression<T, TensorMultiplier<T, E1, I>>::value_type;
    /* ==================================================================================================== */
private:
    E1 const&       _x;                                 //!< First expression for multiplication
    IndexMap<I>     _mult_dims;                         //!< Dimensions of _x to multiply
public:
     // =====================================================================================================
     //! @brief     Sets the expressions for multiplication.
     //! @param[in] x       The first expression for addition.
     // =====================================================================================================
    template <typename... Is>
    TensorMultiplier(TensorExpression<T,E1> const& x, I dim, Is... dims) 
    : _x(x), _mult_dims(dim, dims...)
    {}
   
    // ======================================================================================================
    //! @brief     Gets the sizes of the all the dimensions of the expression.
    //! @return    A constant reference to the dimension size vector of the expression.
    // ======================================================================================================
    const std::vector<size_type>& dimSizes() const { return _x.dimSizes(); }
    
    // ======================================================================================================
    //! @brief     Returns the size of the expression.
    //! @return    The size of the TensorMultiplier.
    // ====================================================================================================== 
    size_type size() const { return _x.size(); }
    
    // ======================================================================================================
    //! @brief     Multiplies two elements (one from each Tensor) from the Tensor expression data.
    //! @param[in] i   The element in the expression which must be fetched.
    //! @return    The result of the multiplication of the Tensors.
    // ======================================================================================================
    value_type operator[](size_type i) const { return _x[i]; }

    // ======================================================================================================
    //! @brief      Const version. Gets the dimensions of _x which are used in the multiplication.           \n
    //!             If for a Tensor x, with say 3 dimensions (i,j,k) each of size 2, then if the             \n
    //!             multiplication (note Tensor multiplication) was:                                         \n
    //!                                                                                                      \n
    //!             z(j) = y(i) * x(i, j)                                                                    \n
    //!                                                                                                      \n
    //!             Where z and y are also Tensors, then this function returns a map with keys i and j,      \n
    //!             with values 0 and 1 respectively, since those are their indices as arguments to the      \n
    //!             () operator.
    //! @return     The map of dimensions to use for the multiplication and their argument numbers.
    // ======================================================================================================
    const IndexMap<I>& multDims() const { return _mult_dims; }
   
    // ======================================================================================================
    //! @brief      Non-const version. Gets the dimensions of _x which are used in the multiplication.       \n
    //!             If for a Tensor x, with say 3 dimensions (i,j,k) each of size 2, then if the             \n
    //!             multiplication (note Tensor multiplication) was:                                         \n
    //!                                                                                                      \n
    //!             z(j) = y(i) * x(i, j)                                                                    \n
    //!                                                                                                      \n
    //!             Where z and y are also Tensors, then this function returns a map with keys i and j,      \n
    //!             with values 0 and 1 respectively, since those are their indices as arguments to the      \n
    //!             () operator.
    //! @return     The map of dimensions to use for the multiplication and their argument numbers.
    // ======================================================================================================
    IndexMap<I>& multDims() { return _mult_dims; }
};    

// ==========================================================================================================
//! @class      TensorMultiplication    
//! @brief      Expression class which multiplies 2 TensorExpressions.
//! @tparam     T   The data type used by the Expressions.
//! @tparam     E1  The first expression to multiply.
//! @tparam     E2  The second expression to multiply.
// ==========================================================================================================
template <typename T, typename E1, typename E2, size_t R>
class TensorMultiplication : public TensorExpression<T, TensorMultiplication<T, E1, E2, R>> {
public:
    /* ====================================== Typedefs ==================================================== */
    using typename TensorExpression<T, TensorMultiplication<T, E1, E2, R>>::container_type;
    using typename TensorExpression<T, TensorMultiplication<T, E1, E2, R>>::size_type;
    using typename TensorExpression<T, TensorMultiplication<T, E1, E2, R>>::value_type;
    /* ==================================================================================================== */ 
private:
    E1&                                 _x;                 //!< Left side expression to multiple
    E2&                                 _y;                 //!< Right side expression to multiply
    std::unordered_map<size_t, size_t>  _reduce_dims;       //!< Dimensions of expressions to be reduced
    std::set<size_t>                    _nreduce_dims_x;    //!< Dimensions of x not to be reduced
    std::set<size_t>                    _nreduce_dims_y;    //!< Dimensions of y not to be reduced
    std::vector<size_type>              _dim_sizes;         //!< Sizes of the dimensions of the resul
    std::vector<size_type>              _index_map;         //!< Mapping of an index to its N-dimensions
public:
    // ======================================================================================================
    //! @brief      Sets the expressions and created the maps of dimensions to reduce and to not reduce.
    //! @param[in]  x   The first (left) expression for multiplication. (Not const as it is intended to be a 
    //!             temporary expression).
    //! @param[in]  y   The second (right) epression for multiplication. (Not const as it is intended to be a
    //!             temporary expression).
    // ======================================================================================================
    TensorMultiplication(TensorExpression<T, E1>& x, TensorExpression<T, E2>& y)
    : _x(x), _y(y), _dim_sizes(0), _index_map(0)
    {
        buildDimensions();
        setDimSizes();
    }
        
    // ======================================================================================================
    //! @brief     Gets the sizes of the all the dimensions of the expression.
    //! @return    A constant reference to the dimension size vector of the expression.
    // ======================================================================================================
    const std::vector<size_type>& dimSizes() const { return _dim_sizes; }
    
    // CHANGE
    // ======================================================================================================
    //! @brief     Returns the size of the expression.
    //! @return    The size of the TensorMultiplier.
    // ====================================================================================================== 
    size_type size() const { return _x.size(); }
    
    // CHANGE
    // ======================================================================================================
    //! @brief     Multiplies two elements (one from each Tensor) from the Tensor expression data.
    //! @param[in] i   The element in the expression which must be fetched.
    //! @return    The result of the multiplication of the Tensors.
    // ======================================================================================================
    value_type operator[](size_type i) const { return _x[i]; }
    
    // ======================================================================================================
    //! @brief      Creates a unordered_map of common dimensions which must be reduced or contracted (see    \n
    //!             Tensor contraction), and two sets of dimensions which must not be - one for each of the  \n
    //!             expressions to multiply. For example, if there are two tensors, say x and y, and they    \n
    //!             are being multiplied to make a Tensor z, then as per Tensor multiplication when using    \n
    //!             Einstein summation convention, the result is:                                            \n
    //!                                                                                                      \n
    //!             z_ik = x_ijk * y_jilm                                                                    \n
    //!                                                                                                      \n
    //!             Since j and i are common to both, they are reduced dimensions, while k, l and m are not  \n
    //!             reduced. To perform the multiplication, the reduced and non-reduced dimensions and their \n
    //!             indices in the subscript notation need to be known, thus the function builds the         \n
    //!             following maps:                                                                          \n
    //!                                                                                                      \n
    //!             reduced = [{key, value}...]         , key = index in 1st expression to multiply (x)
    //!                                                 , value = index in 2nd expression to multiply (y)    \n
    //!                                                                                                      \n
    //!             nreduced_x = [value, ...]           , value = index in 1st expression to multiply (x)    \n
    //!             nreduced_y = [value, ...]           , value = index in 2st expression to multiply (y)    \n
    //!                                                                                                      \n
    //!             Thus for the example above the maps would be built as:                                   \n
    //!                                                                                                      \n
    //!             reduced = [ {0, 1}, {1, 0} ]                                                             \n
    //!             nreduced_x = [ 2 ]                                                                       \n
    //!             nreduced_y = [ 2, 3 ]
    // ======================================================================================================
    void buildDimensions() 
    {
        for (auto& dim_x : _x.multDims()) {                                     // Search all x dims
            auto dim_y = _y.multDims().find(dim_x.first());                     // Check is dim_x is in y dims
            if (dim_y != _y.multDims().end()) { 
                // Insert the dimension using the index of the element in
                // x's subscript list(see above) as the key and the index 
                // of the element in y's subscript list as the value
                _reduce_dims.emplace(dim_x.second, dim_y->second);
                _y.multDims().erase(dim_y);                                     // Remove found element
            } else {
                // Insert the dimension in the set of dimensions not 
                // to reduce for x, the value inserted is the index of
                // the dimension in x's subscript list
                _nreduce_dims_x.insert(dim_x.second);
            }
        }
        for (auto& dim_y : _y.multDims()) {
            // Insert the dimension in the set of dimensions not 
            // to reduce for y, the value inserted is the index of
            // the dimension in y's subscript list
            _nreduce_dims_y.insert(dim_y.second);                              
        }
    }
    
    // ======================================================================================================
    //! @brief      Sets the sizes of the dimensions of the result of the multiplication
    // ======================================================================================================
    void setDimSizes() 
    {
        for (auto& dim : _nreduce_dims_x) _dim_sizes.push_back(_x.dimSizes()[dim]);
        for (auto& dim : _nreduce_dims_y) _dim_sizes.push_back(_y.dimSizes()[dim]);
    }
    
    // ======================================================================================================
    //! @brief      Takes an index in a single dimension contiguous array which represents a                 \n
    //!             multi-dimensional array and maps it to get the indices of each of the dimensions which   \n
    //!             represent the index.
    //! @param[in]  idx     The index of the element in the contiguous array.
    // ======================================================================================================
    template <size_t i = 0>
    typename std::enable_if<i == 0, std::vector<size_type>&>::type
    mapIndex(size_type idx) 
    {
        std::vector<size_type> prev_dim_sizes;                      // Sizes of the dimensions already used
        
        tensor::DimensionMapper<i> mapper;                          // Create mapper and add mapping for the
        _index_map.push_back(mapper(idx, _dim_sizes[i]));           // first non reduced dimension
        prev_dim_sizes.push_back(_dim_sizes[i]);                    // Add dim size to prev dim sizes 
        
        return mI<i + 1>(idx, prev_dim_sizes);
    }

    template <size_type i>
    mI(size_type idx, std::vector<size_type>& prev_dim_sizes)
    {
        size_type dim_offset = std::accumulate(_dim_sizes.begin()           ,
                                               _dim_sizes.begin() + i       ,
                                               1                            ,
                                               std::multiplies<size_type>() );
        
        tensor::DimensionMapper<i> mapper;
        _index_map.push_back(mapper(idx, _dim_sizes[i], prev_dim_sizes));
            
        if (_index_map.size() < _dim_sizes.size()) {
            return mI<i + 1> (idx, prev_dim_sizes);
        } else {
            return _index_map;
        }
    }
};

// ==========================================================================================================
//! @class      TensorSlice
//! @brief      Expression class used to slice a TensorExpression by dimension.
//! @tparam     T   The type of data used by the tensor.
//! @tparam     E   The expression to slice.
//! @tparam     Ts  The types of the variables used to represent the dimensions to slice.
// ==========================================================================================================
template <typename T, typename E, typename... Ts>
class TensorSlice : public TensorExpression<T, TensorSlice<T, E, Ts...>> {
public:
    /* ======================================== Typedefs ================================================== */
    using typename TensorExpression<T, TensorSlice<T,E,Ts...>>::container_type;
    using typename TensorExpression<T, TensorSlice<T,E,Ts...>>::size_type;
    using typename TensorExpression<T, TensorSlice<T,E,Ts...>>::value_type;
    /* ==================================================================================================== */ 
private:
    // Note : These are mutable because this class is essentially a functor without state an is intended to 
    //        be used as a functor once. The mutable memebers are really just temporary variables which hold
    //        state during the dimension mapping computations, thus it is okay to modify them. However, the 
    //        function which modifies them need to be const to access _x, hence they are mutable.
    E const&                        _x;                 //!< Expression to slice
    mutable Tuple<Ts...>            _slice_dims;        //!< Dimensions of the sliced Expression
    mutable std::vector<size_type>  _prev_slice_dims;   //!< Dimensions used for iterative index mapping
    mutable std::vector<size_type>  _slice_dim_sizes;   //!< Sizes of the dimensions for the sliced Expression
    mutable size_type               _index;             //!< Mapped index from the slice to the Expression
    mutable size_type               _offset;            //!< Offset in the Expression due to its 0 dimension
    size_type                       _slice_size;        //!< Size (number of elements) of the slice
public:        
     // =====================================================================================================
     //! @brief     Initializes member variables, builds vector of dimensions of the Expression to slice, and 
     //!            determines the size of the slice.
     //! @param[in] x           The Expression to slice.
     //! @param[in] slice_dims  The dimension of Expression which make up the slice.
     // =====================================================================================================
    TensorSlice(TensorExpression<T, E> const& x, Tuple<Ts...> slice_dims)
    : _x(x), _index(0), _offset(0), _prev_slice_dims(0), 
      _slice_size(buildSliceDimSizes()), _slice_dims(slice_dims) 
    {}
  
    // ======================================================================================================
    //! @brief     Returns the size of the expression
    //! @return    The size of the TensorExpression
    // ======================================================================================================   
    size_type size() const { return _slice_size; }
    
    // ======================================================================================================
    //! @brief      Returns the sizes of each of the dimensions of the slice.
    //! @return     A constant reference to the dimension sizes vector of the slice.
    // ======================================================================================================
    const std::vector<size_type>& dimSizes() const { return _slice_dim_sizes; }

    // ======================================================================================================
    //! @brief     Gets an element from the Expression data which should be in position i of the slice's data.
    //! @param[in] i   The element in the expression which must be fetched.
    //! @return    The value of the element at position i of the expression data.
    // ======================================================================================================
    value_type operator[](size_type i) const { return _x[mapIndex(i)]; }
private:
    // ======================================================================================================
    //! @brief     Adds the size of a dimension from the Expression to the slice dimension sizes vector so 
    //!            that all dimension sizes of the slice are known. Case for all iterations but the last.
    //! @tparam    i   The iteration of the function.
    // ======================================================================================================
    template <size_type i = 0>
    typename std::enable_if<i != (sizeof...(Ts) - 1), size_type>::type buildSliceDimSizes() const
    {
        _slice_dim_sizes.push_back(_x.size(get<i>(_slice_dims)()));                 // Add dimension i's size
        return ( _x.size(get<i>(_slice_dims)()) *                   // Get size of dim i from the Expression
                 buildSliceDimSizes<i + 1>()    );                  // Multiply with the remaining dimensions
    }

    // =====================================================================================================
    //! @brief     Adds the size of a dimension from the Expression to the slice dimension sizes vector so 
    //!            that all dimensions sizes of the slice are known. Case for the last iteration.
    //! @tparam    i   The iteration of the function.
    // =====================================================================================================
    template <size_type i>
    typename std::enable_if<i == (sizeof...(Ts) - 1), size_type>::type buildSliceDimSizes() const 
    {
        _slice_dim_sizes.push_back(_x.size(get<i>(_slice_dims)()));                 // Add last dimension size 
        return _x.size(get<i>(_slice_dims)());                  // Get size of last dimension of the Expression
    }
    
    // =====================================================================================================
    //! @brief         Takes the index of an element in the slice, and maps the index to and element in the 
    //!                Expression being sliced. Case for all iterations but the last.
    //! @param[in]     idx     The index of the element in the slice.
    //! @return        The index of the element i in the slice, in the Expression's data variable.
    //! @tparam        i       The iteration of the function, essentially which element (in the vector of
    //!                slice dimensions) the offset in the Expression's is being determined.
    // =====================================================================================================
    template <size_type i = 0>
    typename std::enable_if<i != (sizeof...(Ts) - 1), size_type>::type mapIndex(size_type idx) const 
    {
        size_type mapped_dim = 0, dim = 0, dim_offset = 0;

        dim         = get<i>(_slice_dims)();                                        // Size of dim i
        dim_offset  = std::accumulate(_x.dimSizes().begin()           ,             // Index offset of i in 
                                      _x.dimSizes().begin() + dim     ,             // original tensors memory
                                      1                               ,
                                      std::multiplies<size_type>()    );
        
        tensor::DimensionMapper<i> mapper;                                      // Get index in dimension i of
        mapped_dim = mapper(idx, _x.dimSizes()[dim]);                           // idx in tensor being sliced
                
        dim == 0  ? _index   = mapped_dim
                  : _offset += dim_offset * mapped_dim;
        
        _prev_slice_dims.push_back(dim);
        return mapIndex<i + 1>(idx);                                // Continue until all dimensions finished
    }
    
    // =====================================================================================================
    //! @brief         Takes the index of an element in the slice, and maps the index to and element in the 
    //!                Expression being sliced. Case for the last iteration.
    //! @param[in]     idx     The index of the element in the slice.
    //! @return        The index of the element i in the slice, in the Expression's data variable.
    //! @tparam        i       The iteration of the function, essentially which element (in the vector of
    //!                slice dimensions) the offset in the Expression's is being determined.
    // =====================================================================================================
    template <size_type i>
    typename std::enable_if<i == (sizeof...(Ts) - 1), size_type>::type mapIndex(size_type idx) const 
    {
        size_type mapped_dim = 0, dim = 0, dim_offset = 0;
        
        dim         = get<i>(_slice_dims)();                                        // Size of dim i 
        dim_offset  = std::accumulate(_x.dimSizes().begin()           ,             // Index offset of i in 
                                      _x.dimSizes().begin() + dim     ,             // original tensors memory
                                      1                               ,
                                      std::multiplies<size_type>()    );
        
        tensor::DimensionMapper<i> mapper;                                      // Get index of dimension i of
        mapped_dim = mapper(idx, _x.dimSizes()[dim], _prev_slice_dims);         // idx in tensor being sliced
                
        dim == 0  ? _index   = mapped_dim
                  : _offset += dim_offset * mapped_dim;
        
        size_type total_offset = _index + _offset;                                  // Calculate final offset
        _prev_slice_dims.clear();                                                   // Reset all class vars
        _index = 0; _offset = 0;
    
        return total_offset;
    }
};

}       // End namespace frnn

/* =========================== Global Operator Overloads using Tensor Expressions ========================= */

namespace {
    
// ==========================================================================================================
//! @brief      Subtracts two TensorExpressions.
//!
//!             The expressions could be any type: Tensor, TensorSubtraction, TensorMultiplication ...
//! @param[in]  x   The TensorExpression to substract from.
//! @param[in]  y   The TensorExpression to subtract with. 
//! @return     The result of the subtraction of the two TensorExpressions.
//! @tparam     T   Type of data used by the expressions.
//! @tparam     E1  Type of the expression to subtract from.
//! @tparam     E2  Type of the expression to subtract with.
// ==========================================================================================================
template <typename T, typename E1, typename E2>
frnn::TensorDifference<T, E1 ,E2> const operator-(frnn::TensorExpression<T, E1> const& x, 
                                                  frnn::TensorExpression<T, E2> const& y)    
{
    return frnn::TensorDifference<T, E1, E2>(x, y);
}

// ==========================================================================================================
//! @brief      Adds two TensorExpressions. 
//!
//!             The expressions could be any Tensor type: Tensor, TensorAddition, TensorMultiplication ...
//! @param[in]  x   The TensorExpression to add to.
//! @param[in]  y   The TensorExpression to add with.
//! @return     The result of the addition of the two TensorExpressions.
//! @tparam     T   The type of data used by the expressions.
//! @tparam     E1  The type of the expression to add to.
//! @tparam     E2  The type of the expression to add with.
// ==========================================================================================================
template <typename T, typename E1, typename E2>
frnn::TensorAddition<T, E1 ,E2> const operator+(frnn::TensorExpression<T, E1> const& x, 
                                                frnn::TensorExpression<T, E2> const& y)    
{
    return frnn::TensorAddition<T, E1, E2>(x, y);
}

// ==========================================================================================================
//! @brief      Multiplies two TensorExpressions (actually only multiplies two TensorMultipliers for the
//!             moment
//! @param[in]  x   The TensorExpression on the left of the multiplcication operand..
//! @param[in]  y   The TensorExpression to the right of the multiplication operand.
//! @return     The result of the addition of the two TensorExpressions.
//! @tparam     T   The type of data used by the expressions.
//! @tparam     E1  The type of the left expression to multiply.
//! @tparam     E2  The type of the right expression to multiply.
// ==========================================================================================================
template <typename T, typename E1, typename E2>
frnn::TensorMultiplication<T, E1 ,E2, 4> const operator*(frnn::TensorExpression<T, E1>& x, 
                                                         frnn::TensorExpression<T, E2>& y)    
{
    return frnn::TensorMultiplication<T, E1, E2, 4>(x, y);
}
} // End global namespace

#endif
