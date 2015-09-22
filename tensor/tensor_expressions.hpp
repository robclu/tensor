// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor expressions for the tensor library -- includes all partial specializations
///         for the tensor expressions. The file is intended to be included in an aplication where all tensor
///         expression functionality is required. It will reduce compilation time, so when using a specific 
///         expression implementation -- say static contatiers with a GPU -- include only that file.
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

#ifndef FTL_TENSOR_EXPRESSIONS_HPP
#define FTL_TENSOR_EXPRESSIONS_HPP

#include "tensor_expression_dynamic_cpu.hpp"
#include "tensor_expression_static_cpu.hpp"

#endif          // FTL_TENSOR_EXPRESSIONS_HPP

