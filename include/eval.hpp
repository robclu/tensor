// ----------------------------------------------------------------------------------------------------------
/// @file   eval.hpp
/// @brief  Header file for the eval metaclass to evaluate meta functions and classes
// ----------------------------------------------------------------------------------------------------------


/*
 * ----------------------------------------------------------------------------------------------------------
 * Eval header file for ftl library.
 * Copyright (C) 2015 Rob Clucas
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * ----------------------------------------------------------------------------------------------------------
 */

// ----------------------------------------------------------------------------------------------------------
// NOTES:
//      - The following conventions are followed:
//          : A     : Used to mean a single argumnet
//          : I     : Used to mean a single arithmetic types
//          : T     : Used to mean a single type
//          : As    : Used to mean variadic arguments
//          : Is    : Used to mean variadic arithmetic types
//          : Ts    : Used to mean variadic types
//          : Us    : Used to mean variadic types if Ts is also used in the function
// ----------------------------------------------------------------------------------------------------------

#ifndef FTL_EVAL
#define FTL_EVAL

namespace ftl {

// ----------------------------------------------------------------------------------------------------------
/// @struct     ArgList
/// @brief      A list of arguments
/// @tparam     As          The list of types which make up the arguments
// ----------------------------------------------------------------------------------------------------------
template <typename... As>
struct ArgList;

// An ArgList with no arguments.
using NoArgs = ArgList<>;

// ----------------------------------------------------------------------------------------------------------
/// @struct     Expand 
/// @brief      Expands a list into its types.
/// @tparam     E           The expression to expand
/// @tparam     A           The argument to expand into the expression
/// @tparam     Expandable  If the expression E is expandable
// ----------------------------------------------------------------------------------------------------------
template <typename E, typename A, bool Expandable>
struct Expand;

// ----------------------------------------------------------------------------------------------------------
/// @struct     Eval 
/// @brief      Evaluates an expression with arguments
/// @tparam     E           The expression to evaluate
/// @tparam     A           The argument to evaluate the expression with
// ----------------------------------------------------------------------------------------------------------
template <typename E, typename A>
struct Eval
{
    // Base case, evaluates to the expression itself
    using value = E;
};

// Specializing Expand - we needed Eval's definition first

// Case for when the the expression is not expandable
template <typename E, typename A>
struct Expand<E, A, false>
{
    // If not expandable then expression evaluates to itself
    using value = E; 
};

// Case for when the expression is expandable 
template <typename E, typename A>
struct Expand<E, A, true>
{
    using value = typename Eval<E, A>::value;
};

// Coming back to specialize Eval now

// Case for when there are no arguments
template <typename E>
struct Eval<E, NoArgs>
{
    // Expression must evaluate to itself
    using result = E;
};

// Case for when the expression is actually a meta-function
template <template <typename...> class F, typename... As>
struct Eval<F<As...>, NoArgs>
{
    // Get the function type when each argument
    // of As is applied to the function F
    using function = F<typename Expand<As, NoArgs, true>::result...>;
    
    // The value is then the function type
    using value = typename function::type;
};

}   // End namespace ftl

#endif
