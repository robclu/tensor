
//The typelist template
template<typename... Ts>
struct list{};

template <int I>
struct int_tt
{
  using type = int_tt<I>;
  
  static constexpr int value = I;
  
  static constexpr bool condition = I != -1 ? true : false;
};
  
template <typename T, typename L>
struct index_of;
 
//Again that recursive head:tail traversal of functional languages
template<typename T , typename HEAD , typename... TAIL>
struct index_of<T,list<HEAD,TAIL...>>
{
 static constexpr int next_value = index_of<T, list<TAIL...>>::value;
 static constexpr int value = next_value >= 0 ? next_value + 1 : -1; //Propagate the -1 or the index
};
 
//First base case: The type is found (T matches HEAD)
template<typename T, typename... Tail>
struct index_of<T, list<T, Tail...>>
{
 static constexpr int value = 0;
};

//Second base case: The type is not found (There are no more types on the list to match with)
template<typename T>
struct index_of<T,list<>>
{
 static constexpr int value = -1;
};

  #include <type_traits>

// -----------------------------------------------------------------


template <template <typename...> class F, typename... Ts>
struct filter;
  
template <template <typename...> class F, typename... P, typename T, typename... Ts>
struct filter<F, list<T, Ts...>, list<P...>>
{
  using passed =  typename std::conditional<
    					F<T>::value,
  						list<P..., T>,
  						list<P...> >::type;
  
  // Pass on result
  using result = typename filter<F, list<Ts...>, passed>::result;
};

// Base case
template <template <typename...> class F,  typename... P>
 struct filter<F,  list<>, list<P...>>
{
  using result = list<P...>;
};
  

 template <template <typename...> class F, typename P, typename L1, typename L2>
struct zip;
  
template <template <typename...> class F, typename... P, typename T, typename... Ts, typename U, typename... Us>
struct zip<F, list<T, Ts...>, list<U, Us...>, list<P...>>
{
  using passed = typename std::conditional<
    						F<T, U>::value,
  							list<P..., T, U>,
  							list<P...>>::type;
  
  using result = typename zip<F, list<Ts...>, list<Us...>, passed>::result;
};

// base case
template <template <typename...> class F, typename... P>
struct zip<F, list<>, list<>, list<P...>>
{
  using result = list<P...>;
};




template <typename L1, typename L2>
  struct find_common;
  
template <typename H1, typename... T1, typename H2, typename... T2>
  struct find_common<list<H1, T1...>, list<H2,T2...>>
{
   static constexpr int value = index_of<H1, list<H2, T2...>>::value;
    
   using indices= list< int_tt< index_of<H1, list<H2, T2...>>::value >,
    				    int_tt< index_of<T1, list<H2, T2...>>::value>...>;
   
   
   template <typename T>
   struct function 
   {
     static constexpr bool value = T::value != -1 ? true : false;
   };
    
   // Filer
   using llist = filter<function, indices, list<>>;
      //ing type = list< typename std::enable_if< index_of<T1, list<H2, T2...>>::found,
   //							           int_tt< index_of<T1, list<H2,T2...>>::value>::type>...>;

   
   template <typename T>
   struct f2 
   {
     static constexpr bool value = T::value == -1 ? true : false;
   };
    
   using ucom = filter< f2, indices, list<>>;

};


   	template <typename T, typename U>
    struct func
    {
      static constexpr bool value = U::value != -1 ? true : false;
    };

 #include <iostream>
  
int main() 
{
  using l1 = list< int_tt<2>, int_tt<4>, int_tt<9>>;
  using l2 = list< int_tt<7>, int_tt<2>, int_tt<4> >;

  using nsc = find_common< l1, l2 >::indices::t;
  
  using cool = find_common< l1, l2>::llist::result;
  using cooler = find_common< l1, l2>::ucom::result;
  
  using ilist = list<int_tt<0>, int_tt<1>, int_tt<2>>;
    
  using tlist = zip< func, ilist, nsc, list<>>::result::t;
  
  int k = index_of< int_tt<-1>, cool>::value;
  
  //std::cout << std::integral_constant<bool, j::value >= 0>;
}
