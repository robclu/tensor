
#ifndef _FTL_OPERATIONS_
#define _FTL_OPERATIONS_

#include "list.hpp"

namespace ftl {
 
template <template <typename...> class C, typename Types>
struct ListApply;

template <template <typename...> class C, typename... Types>
struct ListApply<C, List<Types...>>
{
    using type = C<Types...>;
};

}

#endif
