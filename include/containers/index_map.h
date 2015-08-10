// ==========================================================================================================
//! @file index_map.h
//!       Header file for the fastRNN IndexMap class to create a hastable where the keys as Indexes and
//!       each key has a value which is equal to number the element was inserted into the map.
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

#ifndef _FRNN_CONTAINERS_ORDERED_MAP_
#define _FRNN_CONTAINERS_ORDERED_MAP_

#include "index.h"

#include <unordered_map>
#include <algorithm>
#include <typeinfo>

namespace frnn {

// ==========================================================================================================
//! @struct     IndexMap
//! @brief      Creates an IndexMap  where each of the arguments are the keys (an Index) and the values are 
//!             position the key was inserted into the map i.e it is its index in the map as if the map
//!             was a vector, thus the map can be searched for an Index quickly (since it is the key) but the
//!             index of the Index in the map can also be found (which is usefull when passing a variable 
//!             number of Index elements as arguments to a function).
//!             in constant time while still being able to determine their order.
//! @tparam     K       The type of the keys for the map (the Index class or a similar functor class).
// ==========================================================================================================
template <typename K>    
struct IndexMap {
public:
    /* ======================================== Typedefs ================================================== */
    typedef std::unordered_map<K, size_t, IndexHasher>      map;
    typedef typename map::size_type                         size_type;
    typedef typename map::iterator                          iterator;
    typedef typename map::const_iterator                    const_iterator;
    /* ==================================================================================================== */ 
private:
    std::unordered_map<K, size_type, IndexHasher>           _elements;          //!< Key-value pair elements   
public:
    // ======================================================================================================
    //! @brief      Default constructor.
    // ======================================================================================================
    IndexMap() {}
    
    // ======================================================================================================
    //! @brief      Adds all arguments as keys in the map, which the value being the element's argument index.
    //! @param[in]  element     The first element (key) to add to the map.
    //! @param[in]  elements    The other elements (keys) to add to the map.
    //! @tparam     Ks          The types of the other elements (keys) to add to the map.
    // ======================================================================================================
    template <typename... Ks>
    IndexMap(K element, Ks... elements) 
    {
        createMap<0>(element, elements...);
    }    
        
    // ======================================================================================================
    //! @brief      Creates an unordered_map - terminating case.
    //! @param[in]  element     The element to add to the map.
    //! @tparam     iter        The iteration of the createMap function.
    //! @tparam     E           The type of the element to add to the mao.
    // ======================================================================================================
    template <size_type iter, typename E>
    void createMap(E element)
    {
        _elements.insert(std::make_pair<K, size_type>(static_cast<K>(element), iter));
    }
    
    // ======================================================================================================
    //! @brief      Creates an unordered_map - case for all but the terminating case.
    //! @param[in]  element     The element to add to the map.
    //! @param[in]  elements    The other elements still to be added to the map.
    //! @tparam     iter        The iteration number of the createMapfunction.
    //! @tparam     E           The type of the element to add to the map.
    //! @tparam     Es          The types of the other elements to add to the map.
    // ======================================================================================================
    template <size_type iter = 0, typename E, typename... Es>
    void createMap(E element, Es... elements)
    {
        _elements.insert(std::make_pair<K, size_type>(static_cast<K>(element), iter));
        createMap<iter + 1>(elements...);
    }

    // ======================================================================================================
    //! @brief      Inserts an element into the map.
    //! @param[in]  key     The key of the element to add.
    // ======================================================================================================
    void insert(K&& key) 
    {
        _elements.insert(std::make_pair<K, size_type>(static_cast<K>(key), _elements.size()));
    }
   
    // ======================================================================================================
    //! @brief      Moves an element from one map to this map.
    //! @param      it      The iterator to move to this map.
    // ======================================================================================================
    void insert(iterator it) 
    {
        _elements.insert(std::move(*it));
    }
   
    // ======================================================================================================
    //! @brief      Inserts an element into the map.
    //! @param[in]  key     The key of the element to add.
    // ======================================================================================================
    void insert(K& key) 
    {
        _elements.insert(std::make_pair<K, size_type>(std::move(key()), _elements.size()));
    }

    // ======================================================================================================
    //! @brief      Erases an element with a specified key, if the key is valid for the map, otherwise leaves 
    //!             the map unchanged.
    //! @param[in]  key     The key of the element to remove.
    //! @return     The number of elements which were removed from the map.
    // ======================================================================================================
    size_type erase(const K& key) 
    {
        return _elements.erase(key);
    }
   
    // ======================================================================================================
    //! @brief      Erases an element pointer to by an iterator.
    //! @param[in]  pos     The position of the element to remove.
    //! @return     A new iterator pointing to the element after the removed one.
    // ======================================================================================================
    iterator erase(iterator pos) 
    {
        return _elements.erase(pos);
    }
    
    // ======================================================================================================
    //! @brief  Gets the size of the map.
    //! @return The size of the map.
    // ======================================================================================================
    size_type size() const { return _elements.size(); }
    
    // ======================================================================================================
    //! @brief  Gets an iterator to the start of the map.
    //! @return A constant iterator which points to the beginning of the map.
    // ======================================================================================================
    const_iterator begin() const { return _elements.begin(); }
    
    // ======================================================================================================
    //! @brief  Gets an iterator to the start of the map.
    //! @return An iterator which points to the beginning of the map.
    // ======================================================================================================
    iterator begin() { return _elements.begin(); }
   
    // ======================================================================================================
    //! @brief  Gets an iterator to the end of the map.
    //! @return A constant iterator which points to the end of the map.
    // ======================================================================================================
    const_iterator end() const  { return _elements.end(); }

    // ======================================================================================================
    //! @brief  Gets an iterator to the end of the map.
    //! @return An iterator which points to the end of the map.
    // ======================================================================================================
    iterator end() { return _elements.end(); }    
   
    // ======================================================================================================
    //! @brief  Searches for an element in the map, and if found, returns an iterator to the element,
    //!         otherwise returns an iterator to the end of the map.
    //! @param  key     The key to search for in the map.
    //! @return An iterator which points to the element with a key key if key is a valid key for the map,
    //!         otherwise an iterator to the end of the map.
    // ======================================================================================================
    iterator find(const K& key) { return _elements.find(key()); }

    // ======================================================================================================
    //! @brief  Searches for an element in the map, and if found, returns an iterator to the element,
    //!         otherwise returns an iterator to the end of the map.
    //! @param  key     The key to search for in the map.
    //! @return A constant iterator which points to the element with a key key if key is a valid key for the 
    //!         map, otherwise an iterator to the end of the map.
    // ======================================================================================================
    const_iterator find(const K& key) const { return _elements.find(key()); }
};

}       // End namespace frnn

#endif
