---
layout: page
title: Installation
---

# Contents 

* [Dependencies](#dependancies)
  * [Nano](#nano)
  * [Boost.Test](#boost-test)
* [Building](#building)
* [Compilers](#compilers)
* [Compiling](#compiling)

# Dependencies

* [Nano](https://robclu.github.io/nano) : A template metaprogramming library, which is used to offload some of the work to the compiler, for example things like index mapping for slicing and multiplication.
* [Boost.Test](http://www.boost.org/doc/libs/1_59_0/libs/test/doc/html/index.html) : For the unit testing component of the library. This is not necessary of you aren't running the tests.

__Note:__ At present CUDA is not requires as the GPU component of the library has not yet been implemented.

## Nano

You can get the nano library from here -- [nano](https://github.com/robclu/nano) -- it is a header only library. 
By default it is installed to usr/include. If you install it somewhere else make sure that it is on your ```$PATH``` so that tensor can find it.

## Boost

You can get the Boost test library from here -- [Boost.Test](http://www.boost.org/doc/libs/1_59_0/libs/test/doc/html/index.html) -- and follow the Getting Started Guide to install the libraries.

Note: You only need the test library from Boost, but it is dynamically linked in the Makefile provided with the tensor library, so you should install it to allow dynamic linking (i.e the library needs to be installed and not just the header files).

# Compilers

The following compilers have been tested:

g++ (version 4.9.1)
clang++ (version 3.6.1)


# Compiling

Since tensor is (currently) a header-only library, there is nothing to install if you would just like to use
it in your own application. However, tests are provided with tensor so ensure that everything is qorking as
expected as well as to provide examples of the usage of tensor.

To compile the tests, cd into ```/tensor_v2.0/tests```, at which point you are provided with a few options:

* Make all the tests
* Make an individual tests

## All tests

To make all the tests, simply issue

```
make all (or make -jN all -- to make in parallel with N processes)
```

## Individual tests

The following individual test components are provided 

* tensor_tests -- tests related to tensors specifically
* traits_tets -- tests for the tensor traits
* tensor_container -- tests for the tensor containers
* tensor_operations -- tests for the operations (addition, subtraction etc..)

To make an individual tests, issuse

``` 
make <test_name>
```

with the appropriate test name.
