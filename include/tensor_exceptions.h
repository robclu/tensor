// ==========================================================================================================
//! @file   Header file for fastRNN tensor exception classes.
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

#ifndef _FRNN_TENSOR_EXCEPTION_
#define _FRNN_TENSOR_EXCEPTION_

#include <iostream>
#include <exception>
#include <string>

namespace frnn {

// ==========================================================================================================
//! @class  TensorOutOfRange
//! @brief  Provides exceptions for when a range error occurs for a Tensor.
// ==========================================================================================================
class TensorOutOfRange : public std::exception {
public:
    std::string _message;           //!< Error message for exception.
public:
    // ======================================================================================================
    //! @brief      Sets the error message.
    //! @param[in]  dimension       The dimension of a Tensor from which element access was attempted.
    //! @param[in]  dimension_size  The size of the dimension.
    //! @param[in]  index           The index of the element for which access was attempted.
    // ======================================================================================================
    TensorOutOfRange(const int dimension, const int dimension_size, const int index) 
    : _message("Error : Out of range : Attempted to access invalid tensor element "    + 
                std::to_string(index)                                                  + 
                " of dimension "                                                       +
                std::to_string(dimension)                                              +
                " which has size "                                                     +
                std::to_string(dimension_size)                                         +
                " : Note : tensors are 0 indexed"                                      ) {} 
   
    // ======================================================================================================
    //! @brief      Sets the error message.
    //! @param[in]  dimension   The dimension of the Tensor for which access was attempted.
    //! @param[in]  rank        The rank of the Tensor.
    // ======================================================================================================
    TensorOutOfRange(const int dimension, const int rank) 
    : _message("Error : Out of range : Attempted to access invalid dimension "  +   
                std::to_string(dimension)                                       + 
                " of tensor with rank "                                         +
                std::to_string(rank)                                            +
                " returning value of 0"                                         ) {}
    
    // ======================================================================================================
    //! @brief      Specifying the error message for out of range access on a Tensor.
    //! @return     The error message.
    // ======================================================================================================
    const char* what() const throw() { return _message.c_str(); }
};

// ==========================================================================================================
//! @class      TensorInvalidArguments
//! @brief      Provides the exception for when an invalid number of arguments are provided to a Tensor
//!             function, since many of the functions are variadic, this is a possibility.
// ==========================================================================================================
class TensorInvalidArguments : public std::exception {
public:
    std::string _message;
public:
    // ======================================================================================================
    //! @brief      Sets the error message
    //! @param[in]  num_args_specified  The number of arguments given to the function.
    //! @param[in]  num_args_required   The number of arguments required by the function
    // ====================================================================================================== 
    TensorInvalidArguments(const int num_args_specified, const int num_args_required) 
    : _message("Error : Invalid Arguments for tensor : "    +
                std::to_string(num_args_required)           +
                " arguments required, "                     +
                std::to_string(num_args_specified)          +
                " given"                                    ) {}
    
    // ======================================================================================================
    //! @brief      Specifying the error message for invalid arguments for a Tensor function.
    //! @return     The error message.
    // ======================================================================================================
    const char* what() const throw() { return _message.c_str(); }
};

}   // End namspace frnn

#endif
