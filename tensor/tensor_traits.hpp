// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor traits for tensor library.
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

#ifndef FTL_TENSOR_TRAITS_HPP
#define FTL_TENSOR_TRAITS_HPP

#include "tensor_container.hpp"

namespace ftl {

// So that the code is more readable -- using an int rather than an enum since it will make 
// for easy integration with other libraries that want to enable compile time device selection
using device = short;

static constexpr device CPU = 0;
static constexpr device GPU = 1;

// ----------------------------------------------------------------------------------------------------------
/// @struct     TensorTraits
/// @brief      Traits class which specifies parameters for a tensor, such as what type of container it uses
///             and what type of device the computations should be performed on
/// @tparam     Dtype           The type of data used by the container
/// @tparam     DeviceType      The type of device used for computation -- CPU or GPU
/// @tparam     DimSizes        The sizes of each of the dimensions of the tensor -- an optional parameters.
///             This parameter is used to determine the container type -- static if the dimension sizes are 
///             specified or dynamic if they are not.
// ----------------------------------------------------------------------------------------------------------
template <typename Dtype, device DeviceType, size_t... DimSizes>
struct TensorTraits;

// Specialize for static container
template <typename Dtype, device DeviceType, size_t SizeFirst, size_t... SizeRest>
struct TensorTraits<Dtype, DeviceType, SizeFirst, SizeRest...> {
    // ---------------------------------------- ALIAS'S -----------------------------------------------------
    using data_type         = Dtype;
    using container_type    = TensorContainer<Dtype, SizeFirst, SizeRest...>;
    using data_container    = typename container_type::data_container;
    using dim_container     = typename container_type::dim_container;
    using size_type         = typename container_type::size_type;
    // ------------------------------------------------------------------------------------------------------
    static constexpr device device_type     = DeviceType;
};

// Specialize for dynamic container
template <typename Dtype, device DeviceType>
struct TensorTraits<Dtype, DeviceType> {
    // ---------------------------------------- ALIAS'S -----------------------------------------------------
    using data_type         = Dtype;
    using container_type    = TensorContainer<Dtype>;
    using data_container    = typename container_type::data_container;
    using dim_container     = typename container_type::dim_container;
    using size_type         = typename container_type::size_type;
    // ------------------------------------------------------------------------------------------------------};
    static constexpr device device_type     = DeviceType;
};

}               // End namespace ftl
#endif          // FTL_TENSOR_TRAITS_HPP
