// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for exception classes for the tensor library.
// ----------------------------------------------------------------------------------------------------------

/*
 * ----------------------------------------------------------------------------------------------------------
 *  tensor exceptions header file for tensor library.
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

#ifndef FTL_TENSOR_EXCEPTIONS_HPP
#define FTL_TENSOR_EXCEPTIONS_HPP

#include <iostream>
#include <exception>
#include <string>

namespace ftl {

// ----------------------------------------------------------------------------------------------------------
/// @class  tensor_out_of_range
/// @brief  Provides exceptions for when a range error occurs for a tensor.
// ----------------------------------------------------------------------------------------------------------
class tensor_out_of_range : public std::exception {
public:
    std::string _message;           ///< Error message for exception.
public:
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Sets the error message.
    /// @param[in]  dimension       The dimension of a tensor from which element access was attempted.
    /// @param[in]  dimension_size  The size of the dimension.
    /// @param[in]  index           The index of the element for which access was attempted.
    // ------------------------------------------------------------------------------------------------------
    tensor_out_of_range(const int dimension, const int dimension_size, const int index) 
    : _message("Error : Out of range : Attempted to access invalid tensor element "    + 
                std::to_string(index)                                                  + 
                " of dimension "                                                       +
                std::to_string(dimension)                                              +
                " which has size "                                                     +
                std::to_string(dimension_size)                                         +
                " : Note : tensors are 0 indexed"                                      ) {} 
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Sets the error message.
    /// @param[in]  dimension   The dimension of the tensor for which access was attempted.
    /// @param[in]  rank        The rank of the tensor.
    // ------------------------------------------------------------------------------------------------------
    tensor_out_of_range(const int dimension, const int rank) 
    : _message("Error : Out of range : Attempted to access invalid dimension "  +   
                std::to_string(dimension)                                       + 
                " of tensor with rank "                                         +
                std::to_string(rank)                                            +
                " returning value of 0"                                         ) {}
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Specifying the error message for out of range access on a tensor.
    /// @return     The error message.
    // ------------------------------------------------------------------------------------------------------
    const char* what() const throw() { return _message.c_str(); }
};

// ----------------------------------------------------------------------------------------------------------
/// @class      tensor_invalid_arguments
/// @brief      Provides the exception for when an invalid number of arguments are provided to a tensor
///             function, since many of the functions are variadic, this is a possibility.
// ----------------------------------------------------------------------------------------------------------
class tensor_invalid_arguments : public std::exception {
public:
    std::string _message;               ///< Error message for exception.
public:
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Sets the error message
    /// @param[in]  num_args_specified  The number of arguments given to the function.
    /// @param[in]  num_args_required   The number of arguments required by the function
    // ------------------------------------------------------------------------------------------------------
    tensor_invalid_arguments(const int num_args_specified, const int num_args_required) 
    : _message("Error : Invalid Arguments for tensor : "    +
                std::to_string(num_args_required)           +
                " arguments required, "                     +
                std::to_string(num_args_specified)          +
                " given"                                    ) {}
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Specifying the error message for invalid arguments for a tensor function.
    /// @return     The error message.
    // ------------------------------------------------------------------------------------------------------
    const char* what() const throw() { return _message.c_str(); }
};

}           // End namespace ftl

#endif      // FTL_TENSOR_EXCEPTIONS_HPP
