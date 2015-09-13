// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor library tensor_container class to allow both static and dynamic containers
// ----------------------------------------------------------------------------------------------------------

/*
* ----------------------------------------------------------------------------------------------------------
*  Header file for tensor tensor_container class
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

#ifndef FTL_TENSOR_CONTAINER_HPP
#define FTL_TENSOR_CONTAINER_HPP

#include <nano/nano.hpp>

#include <array>
#include <vector>
#include <iostream>

namespace ftl {
    
template <typename Type, size_t... Sizes>
class tensor_container;

// Specialize for static containers
template <typename Type, size_t SizeFirst, size_t... SizeRest>
class tensor_container<Type, SizeFirst, SizeRest...> {
public:
    using dimension_sizes   = nano::list<nano::size_t<SizeFirst>, nano::size_t<SizeRest>...>;
    using dimension_product = nano::multiplies<dimension_sizes>;
    using container_type    = std::array<Type, dimension_product::result>; 
    
    static constexpr size_t size() { return dimension_product::result; }

    tensor_container() {}

    tensor_container(container_type& data)
    : _data(data) {
        std::cout << "Reference\n";
    };

    template <typename V1, typename... VR> 
    tensor_container(V1 v1, VR... vr) 
    : _data({v1, vr...}) {
        std::cout << "Const\n";
    }
    
    inline Type& operator[](size_t i) { return _data[i]; }
private:
    container_type _data;                                                   //!< Static data for a tensor
};

template <typename Type>
class tensor_container<Type> {
public:
    using container_type = std::vector<Type>;
   
    inline Type& operator[](size_t i) { return _data[i]; }
private:
    container_type _data;                                           //!< Dynamic data container for a tensor
};

}               // End namespace ftl

#endif          // FTL_TENSOR_CONTAINER_HPP
