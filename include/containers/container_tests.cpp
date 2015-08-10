/*
 *  Test file for Tensor List class
 *
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
 */

#include <gtest/gtest.h>
#include <iostream>

#include "list_operations.hpp"
#include "index.h"

#include "new_list.hpp";

#include <string>
#include <algorithm>

template <typename... As>
struct Tso
{
    using list = ftl::List<As...>;
    
    list getList(As... args) 
    {
        return ftl::List<As...>(std::forward<As>(args)...);
    }
};

TEST( List, CanCreateListWithMultipleTypes )
{
    ftl::List<int, char> list(4, 'c');
    EXPECT_EQ( ftl::list::size(list), 2 );
}

TEST( List, CanCreateListWithAnyNumberOfElements )
{
    ftl::List<int, int, float, std::string> list(4, 3, 3.7, "string");
    EXPECT_EQ( ftl::list::size(list), 4 );
}

TEST( List, CanGetListElement )
{
    ftl::List<int, int, float, std::string> list(4, 3, 3.7, "string");
    
    int element = ftl::list::get<1>(list);
    
    EXPECT_EQ( element, 3 );
}

TEST( List, CanSetListElement )
{
    ftl::List<int, int, float, std::string> list(4, 3, 3.7, "string");
    
    ftl::list::get<2>(list) = 4.5;
    
    EXPECT_EQ( 4.5, ftl::list::get<2>(list) );
}

TEST ( List, CanCreateListWithIndexTypes )
{
    using namespace ftl;
    ftl::Idx<0>         i;
    ftl::Idx<1>         j;
    ftl::List<ftl::Idx<0>>    list(i);
    ftl::List<ftl::Idx<1>>    list1(j);
    
    bool b = ftl::is_equal<Idx<0>, Idx<1>>::value;

    constexpr size_t dsize = size2(list, list1);

    EXPECT_EQ( dsize, 2);
    EXPECT_EQ( ftl::list::get<0>(list).val(), 0     );
    EXPECT_NE( b                            , true  );

}

TEST( newList, CanCreateList )
{
    using namespace ftl2;
    using L2 = List<int, int>;
    using L3 = List<int, int, float>;
    using LI = List<ftl::Idx<0>, ftl::Idx<2>, ftl::Idx<1>>;
    
    using LC = concat<L2, L3>::result;
   
    L2      l_1(2, 2);
    L3      l_2(3, 3, 4.f);
      
    L2 nlist = make_list(2, 2);

    auto new_list = join(l_1, l_2);
  
    size_t found = type_index<ftl::Idx<2>, LI>::value;

    size_t found_1 = type_index<float, LC>::value;
    
    std::cout << "IDX: " << found_1 << std::endl;
    
    EXPECT_GE( found, 1 );
    EXPECT_EQ( list_size(l_1), 2 );
}
