// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for tensor library for utility functions and macros
// ----------------------------------------------------------------------------------------------------------

/*
 * ----------------------------------------------------------------------------------------------------------
 *  Header file for tensor utility functions 
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

#ifndef FTL_UTILS_HPP
#define FTL_UTILS_HPP

#include <iostream>

// General assertation macro
#define ASSERT(left, operator, right) {                                                 \
    if(!((left) operator (right))) {                                                    \
        std::cerr << "ASSERT FAILED: " << #left << " " <<  #operator << " " << #right   \
        << " in " << __FILE__ << ":" << __LINE__ << " : " <<                            \
        #left << " = " << (left) << ", " << #right << " = " << (right) << std::endl;    \
    }                                                                                   \
}

#endif 
