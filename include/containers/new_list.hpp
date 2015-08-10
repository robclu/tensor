#ifndef _LIST_
#define _LIST_

namespace ftl2 {

// Helpers

template <size_t... Is> struct indices {};

template <size_t S, size_t N, size_t... Is>
struct index_range;

template <size_t S, size_t... Is>
struct index_range<S, S, Is...>
{
    using type = indices<Is...>;
};

template <size_t S, size_t N, size_t... Is>
struct index_range : public index_range<S, N - 1, N - 1, Is...> {};

template <size_t S, size_t E>
using make_range = typename index_range<S, E>::type;

template <size_t E>
using make_indices = typename index_range<0, E>::type;

template <typename...> struct List;

template <typename T, typename... Ts>
struct List<T, Ts...> {
    constexpr List();
    constexpr List(T t, Ts... ts) : _head(t), _tail(ts...) {};
public:
    T           _head;
    List<Ts...> _tail;
};

template <> struct List<> {};

template <typename... Ts>
List<Ts...> make_list(Ts... ts) { return List<Ts...>(ts...); }

template <typename... Ts>
constexpr size_t list_size(List<Ts...> list ) 
{
    return sizeof...(Ts);
}

template <typename L, size_t I> struct list_element;

template <typename T, typename... Ts, size_t I>
struct list_element<List<T, Ts...>, I> {
    using type = typename list_element<List<Ts...>, I - 1>::type;
};

template <typename T, typename... Ts>
struct list_element<List<T, Ts...>, 0> {
    using type = T;
};

template <typename L, size_t I>
struct get_help {
    static constexpr auto _(L list) -> 
        decltype(get_help<decltype(list._tail), I - 1>::_(list._tail)) {
        return get_help<decltype(list._tail), I - 1>::_(list._tail);
    }
};

template <typename L>
struct get_help<L, 0> {
    static constexpr auto _(L list) ->
        decltype(list._head) {
        return list._head;
    }
};
       
template <size_t I, typename L>
constexpr auto get(L list) ->
    decltype(get_help<L, I>::_(list)) {
    return get_help<L, I>::_(list);
}

template <typename L1, typename L2, size_t ...Is, size_t... Js>
constexpr auto join_help(L1 list1, L2 list2, indices<Is...>, indices<Js...>) ->
    decltype(make_list(get<Is>(list1)..., get<Js>(list2)...)) {
    return make_list(get<Is>(list1)..., get<Js>(list2)...);
}

// No list
template <typename... Ts>
constexpr List<> join() { return List<>(); }

// Single list
template <typename... Ts>
constexpr List<Ts...> join(List<Ts...> list) { return list; }

// Multiple lists
template <typename... L1Ts, typename... L2Ts, typename... Lists>
constexpr auto join(List<L1Ts...> list1, List<L2Ts...> list2, Lists... lists) ->
decltype(join(
            join_help(
                list1, 
                list2, 
                make_indices<sizeof...(L1Ts) - 1>(), 
                make_indices<sizeof...(L2Ts) - 1>()
            ), lists...
        )
    )
{   return join(
        join_help(
            list1, 
            list2,
            make_indices<sizeof...(L1Ts) - 1>(),
            make_indices<sizeof...(L2Ts) - 1>()
        ), lists...
    );
}
    
}
#endif
