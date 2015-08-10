// ==========================================================================================================
//! @file   Header file for Tensor Index struct.
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

#ifndef _FTL_INDICES_
#define _FTL_INDICES_

#include <cstdint>
#include <typeinfo>
#include <type_traits>
#include <iostream>

namespace ftl {


template <size_t i>
struct Idx 
{
    // Compile time
    constexpr static size_t const value = i;
    
    using type = Idx<i>;

    constexpr size_t val() const { return i; }
};

namespace idx {

}
}

#endif
