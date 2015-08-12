*A fast c++ tensor library*

# FTL

FTL is a fast (well hopefully) c++ tensor library. It is designed with both speed and clearity of expression in mind. 
The library makes extensive use of templates, specifically [template metaprogramming](https://en.wikipedia.org/wiki/Template_metaprogramming) to improve performance. [Expression templates](https://en.wikipedia.org/wiki/Expression_templates) are also used to allow mathematical expressions and tensor operations to be expressed exactly as they would be mathematically. 

A lot of the TMP implementations were understood from the following blogs and from endlessly reading the assosciated code on their Github accounts (thanks for the help!) : 

* [Manu Sancheez's blog (see the Turbo library)](http://manu343726.github.io/)
* [Eric Niebler's blog (see his Meta library)](http://ericniebler.com/)

Tests have been written using the [Boost Test library](http://www.boost.org/doc/libs/1_58_0/libs/test/doc/html/index.html) to verify the 'correctness' of all the implemented components. The tests also help to illustrate the usage of the various components of the library.

There will probably be many sections of code which can be improved. Any suggestions and improvements will be much appreciated - please contact me if with either.

# Current Status

Currently the library is CPU only and is single-threaded as the development process has just begun. However, the library will be extended to include GPU functionality (with CUDA) and multi-threading (and therefore multi-core CPU - probably with OpenMP and MPI).

# Conventions

A lot of the inspiration for the library comes from the Boost libraries, hence the style conventions are similar to those used in the Boost libraries. A summary of the conventions used are:

All class and variable names are lowercase with underscore separators:

```c++
class tensor_expression {};
or 
int multiplication_result;
```

All template parameter names are CamelCase starting with a capital letter:

```c++
template <typename Value> struct integer;
``` 

Classes and stucts have an opening brace on the same line (as per Stroustrup), unless the class or struct is a metaclass, in which case the opening brace is on the next line (to make the separation clear and IMHO metaclasses read better with opening braces on the line following the declaration):

```c++
// Not a meta class
template <typename T>
class tensor {
};

// Meta class
template <typename... As>
struct list 
{
  template <template <typename...> class Function>
  stuct apply 
  {
    // Rest of code ...
  };
};
```

Functions, like metaclasses, have braces beginng on the line after the declaration (again as per Stroustrup):

```c++
int multiply(int x, int y) 
{
  return x * y;
}
```

Namespaces have opening braces starting on the same line as the declaration 

```c++
namespace ftl {
}                 // End namespace ftl
```

Class member variables begin with a single underscore, while local variables (and function parameters) do not: 

```c++
class foo {
public:
  int _class_member_variable;
  
  void bar(int variable_one, int variable_two);
};

void foo::bar(int variable_one, int variable_two)
{
  int local_variable = 0;     // No leading single underscore
}  
```

I will update this formally, but for now it may help if reading the code.

# Compiling

A makefile is provided in the include directory which builds the test suite.

Simply issuing ```make release``` from the ```include`` directory will make the test suite. 

All library files are templated header files and thus to use the functionality you simply need to include the relevant header file.

# Examples

To do ...
