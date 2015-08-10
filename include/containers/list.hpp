// ==========================================================================================================
//! @file list.hpp
//!       Header file for a TMP List class to hold any number of elements of any type. 
//!       Additonally, some operations on the List are provided. These are however, limited, and based on 
//!       the functionality required for the Tensor class. 
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
 *  =========================================================================================================
 */ 

#ifndef _FTL_LIST
#define _FTL_LIST_

namespace ftl {

template <typename A, typename B>
struct is_equal {
    constexpr static bool const value = (A::value == B::value);
};
  
// ==========================================================================================================
//! @struct  List
//! @brief   Holds any number of elements of any type.
//! @details Usage : List<type1, type2, ...> list(elem1 of type1, elem2 of type2, ...)
//! @tparam  Ts     The types of the elements to be stored in the List, i.e a typelist.
// ==========================================================================================================
template <typename... Ts> struct List;

// ==========================================================================================================
//! @struct  List
// ==========================================================================================================
template <typename T>
struct List<T> {
public:
    T _back;                                                                        //!< Element of the List
public:
    // ======================================================================================================
    //! @brief      Constuctor for a List when there is only one element (base case of recursive 
    //!             construction).
    //! @param[in]  element     The element to add to the List.
    //! @tparam     T           Type of the element to add to the List.
    // ======================================================================================================
    List(T element) : _back(element) {}
};

// ==========================================================================================================
//! @struct  List 
// ==========================================================================================================
template <typename T, typename... Ts>
struct List<T, Ts...> : List<Ts...> {
public: 
    T _back;            //!< Element of the List
    constexpr static size_t const id = sizeof...(Ts);
    
public:
     // =====================================================================================================
     //! @brief     Constructor for a List when there is more than one element.
     //! @param[in] element     The element to add to the List on this iteration of the recursive 
     //!            construction.
     //! @param[in] elements    The rest of the elements to add to the List on the remaining iterations.
     //! @tparam    T           Type of the element to add to the List. 
     //! @tparam    Ts          The types of the elements to add to the List on the following iterations of 
     //!            the recursive construction.
     //  ====================================================================================================
    List(T element, Ts... elements) : List<Ts...>(elements...), _back(element) {} 

    using type = List<T, Ts...>;
};

// ==========================================================================================================
//! @struct     ListElementTypeHolder
// ==========================================================================================================
template <size_t i, typename T> struct ListElementTypeHolder;

// ==========================================================================================================
//! @struct     ListElementTypeHolder
// ==========================================================================================================
template <typename T, typename... Ts>
struct ListElementTypeHolder<0, List<T, Ts...>> {
    using type = T;         
};

// ==========================================================================================================
//! @struct     ListElementTypeHolder
//! @brief      Defines the types of each of the elements in a List.
//! @tparam i   Index of the element in the List for which the type must be declared. 
//! @tparam T   Type of the element at position i in List./
//! @tparam Ts  Types of the elements at positions != i in the List. 
// ==========================================================================================================
template <size_t i, typename T, typename... Ts>
struct ListElementTypeHolder<i, List<T, Ts...>> {
    using type = typename ListElementTypeHolder<i - 1, List<Ts...>>::type;
};

namespace list {
   
// ==========================================================================================================
//! @brief      Gets the 0th element in a List. Enabled if i is equal to 0.
//! @param[in]  list    The List to get the element from.
//! @tparam     i       The index of the element to get.
//! @tparam     Ts      The types of all elements in the List.
// ==========================================================================================================
template <size_t i, typename... Ts>
typename std::enable_if<i == 0, typename ListElementTypeHolder<0, List<Ts...>>::type&>::type 
get(List<Ts...>& list) 
{
    return list._back;
}

// ==========================================================================================================
//! @brief      Gets the element at position i in the List. Enabled if i is not equal to 0.
//! @param[in]  lsit    The List to get the element from.
//! @tparam     i       The index of the element in the List.
//! @tparam     T       The type of the element at position i.
//! @tparam     Ts      The types of all the elements in the List.
// ==========================================================================================================
template <size_t i, typename T, typename... Ts>
typename std::enable_if<i != 0, typename ListElementTypeHolder<i, List<T, Ts...>>::type&>::type
get(List<T, Ts...>& list) 
{
    List<Ts...>& listBase = list;
    return get<i - 1>(listBase);       
}
    
// ==========================================================================================================
//! @brief      Gets the size of a List
//! @param[in]  list    The List to get the size of.
//! @tparam     Ts      The types of the elements in the List.
//! @return     The size of the List tuple.
// ========================================================================================================== 
template <typename... Ts>
size_t size(List<Ts...>& list) { return sizeof...(Ts); }

}

template <typename... As, typename... Bs>
constexpr size_t size2(List<As...>& l1, List<Bs...>& l2)
{
    return sizeof...(As) + sizeof...(Bs);
}
}       // End namespace ftl

#endif
