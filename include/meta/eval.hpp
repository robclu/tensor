// ----------------------------------------------------------------------------------------------------------
/// @file   eval.hpp
/// @brief  Header file for the eval metaclass to evaluate meta functions and classes
// ----------------------------------------------------------------------------------------------------------


/*
 * ----------------------------------------------------------------------------------------------------------
 * eval header file for ftl library.
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

#ifndef FTL_EVAL
#define FTL_EVAL

#include "numeric_types.hpp"

namespace ftl {

// ----------------------------------------------------------------------------------------------------------
/// @struct     identify
/// @brief      Simply an identifier to identify meta types and meta functions. 
/// @tparam     Type    The type to identify
// ----------------------------------------------------------------------------------------------------------
template <typename Type>
struct identify
{
    using result = Type;
};

// ----------------------------------------------------------------------------------------------------------
/// @struct     args_list
/// @brief      A list of arguments
/// @tparam     Args    The list of types which make up the arguments
// ----------------------------------------------------------------------------------------------------------
template <typename... Args>
struct args_list;

// Define an empty args list
using no_args = args_list<>;

// ----------------------------------------------------------------------------------------------------------
/// @struct     expand 
/// @brief      Expands a list into its types.
/// @tparam     Expression  The expression to expand
/// @tparam     Arg         The argument to expand into the expression
/// @tparam     Expandable  If the expression E is expandable
// ----------------------------------------------------------------------------------------------------------
template <typename Expression, typename Arg, bool Expandable>
struct expand;

// ----------------------------------------------------------------------------------------------------------
/// @struct     eval 
/// @brief      Evaluates an expression with arguments
/// @tparam     Expresison  The expression to evaluate
/// @tparam     Arg         The argument to evaluate the expression with
// ----------------------------------------------------------------------------------------------------------
template <typename Expression, typename Arg>
struct eval
{
    // Base case, evaluates to the expression itself
    using result = Expression;
};

// Specializing expand - we needed eval's definition first

// Case for when the the expression is not expandable
template <typename Expression, typename Arg>
struct expand<Expression, Arg, false>
{
    // If not expandable then expression evaluates to itself
    using result = Expression; 
};

// Case for when the expression is expandable 
template <typename Expression, typename Arg>
struct expand<Expression, Arg, true>
{
    using result = typename eval<Expression, Arg>::result;
};

// Coming back to specialize eval now

// Case for when there are no arguments
template <typename Expression>
struct eval<Expression, no_args>
{
    // Expression must evaluate to itself
    using result = Expression;
};

// Case for when the expression is actually a meta-function
template <template <typename...> class Function, typename... Args>
struct eval<Function<Args...>, no_args>
{
    // Get the function type when each argument
    // of As is applied to the function F
    using function = Function<typename expand<Args, no_args, true>::result...>;
    
    // The value is then the function result
    using result = typename function::result;
};

}   // End namespace ftl

#endif
