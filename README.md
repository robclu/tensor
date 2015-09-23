*A fast c++ tensor library*

# Tensor

Tensor is a c++ tensor expression library. It is designed with both speed and clarity of expression in mind. It it thus intended to provide high levels of performance but allow operations on tensors in the code to appear exactly as they do mathematically. 

[Template metaprogramming](https://en.wikipedia.org/wiki/Template_metaprogramming) is used to 'offload' any work which can be computed at compile time, to the compiler and [expression templates](https://en.wikipedia.org/wiki/Expression_templates) are used to achieve the translation of the mathematically expressed code to high performance code.

Tests have been written using the [Boost Test library](http://www.boost.org/doc/libs/1_58_0/libs/test/doc/html/index.html) to verify the 'correctness' of all the implemented components. The tests also help to illustrate the usage of the various components of the library.

The long term goal is to develop something along the lines of the tensor library in the python theano libray,
but with support for any rank tensors with both CPU and GPU functionality.

# Documentation

Please see [Tensor Documentation](http://robclu.github.io/tensor/) for documentation and usage examples.

# Current Status

Currently the library is CPU only and is single-threaded as the development process has just begun. However, the library will be extended to include GPU functionality (with CUDA and probably also OpenCL) and multi-threading (and therefore multi-core CPU - probably with OpenMP and MPI).

There is quite a lot of functionality which is working at present, however, the first
iteration of the development used vectors as the data containers. I feel that a lot of performance improvement
can be achieved by using static containers and the properties of the tensor which come with knowing the sizes
of the dimensions when the tensor is created.

I did some tests with comparing static vs dynamic tensors and the static tensors were up to 20x faster than dynamic tensors, and even faster than ```std::array``` for element access as the static tensors do the mapping using the dimension sizes at compile time.

I thus decided to completely redesign the interface, allowing a selection between the static and dynamic tensors, as well as a selection between CPU and GPU implementations.

# Dependencies

* [nano](https://github.com/robclu/nano) : A template metaprogramming library, is used to offload some of the work to the compiler, for example things like index mapping for slicing and multiplication.
* [boost unit](http://www.boost.org/doc/libs/1_58_0/libs/test/doc/html/index.html) : For the unit testing
  component of the library. This is not necessary of you aren't running the tests.

# Building

## Nano 

You can get the nano library from here - [nano](https://github.com/robclu/nano) - it is a header only
library. By default it is installed to ```usr/include```. If you install it somewhere else make sure that it
is on your path so that ```tensor``` can find it.

## Boost

You can get the Boost test library from here - [Boost](http://www.boost.org/) - and follow the [Getting Started Guide](http://www.boost.org/doc/libs/1_59_0/more/getting_started/index.html) to install the libraries.

__Note:__ You only need the test library, but it is dynamically linked in the tensor tests provided with the ```tensor``` library, so you should install it to allow dynamic linking (i.e install the test library and not just the ```.hpp``` file.)

## CUDA

GPU functionality is not currently implemented so nothing to be done here.

# Compiling

Tensor has been tested with the following compilers

* g++ (4.9.1)
* clang++ (3.6.1)

Since tensor is (currently) a header-only library, there is nothing to install if you would just like to use it in your own application. However, tests are provided with tensor so ensure that everything is working as expected as well as to provide examples of the usage of tensor.

To compile the tests, cd into ```tests/```, at which point you are provided with a few options:

* Make all the tests
* Make an individual tests

##  All tests

To make all the tests, simply issue
```
make all (or make -jN all -- to make in parallel with N processes)
```

## Individual tests

The following individual test components are provided

* __tensor__ : tests related to tensors specifically
* __traits__ : tests for the tensor traits
* __container__ : tests for the tensor containers
* __operations__ : tests for the operations (addition, subtraction etc...)

To make an individual tests, issuse

```
make <test_name>
```

with the appropriate test name, for example ```make container```

## Cleaning

To clean the tests, issue

```
make clean
```
