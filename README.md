*A fast c++ tensor library*

# Tensor

Tensor is a c++ tensor expression library. It is designed with both speed and clarity of expression in mind. It it thus intended to provide high levels of performance but allow operations on tensors in the code to appear exactly as they do mathematically. 

[Template metaprogramming](https://en.wikipedia.org/wiki/Template_metaprogramming) is used to 'offload' any work which can be computed at compile time, to the compiler and [expression templates](https://en.wikipedia.org/wiki/Expression_templates) are used to achieve the translation of the mathematically expressed code to high performance code.

Tests have been written using the [Boost Test library](http://www.boost.org/doc/libs/1_58_0/libs/test/doc/html/index.html) to verify the 'correctness' of all the implemented components. The tests also help to illustrate the usage of the various components of the library.

The long term goal is to develop something along the lines of the tensor library in the python theano libray,
but with support for any rank tensors with both CPU and GPU functionality.

Please let me know, or submit a patch, any areas of the code which can be improved!

# Current Status

Currently the library is CPU only and is single-threaded as the development process has just begun. However, the library will be extended to include GPU functionality (with CUDA and probably also OpenCL) and multi-threading (and therefore multi-core CPU - probably with OpenMP and MPI).

There is quite a lot of functionality which is working at present (see [usage](#usage)), however, the first
iteration of the development used vectors as the data containers. I feel that a lot of performance improvement
can be achieved by using static containers and the properties of the tensor which come with knowing the sizes
of the dimensions when the tensor is created, so currently I am implementing a static version. 

The final library will have support for both static and dynamic tensors, where the choice will be made based
on the context. 

# Current Development 
# Dependencies

* [nano](https://github.com/robclu/nano) : A template metaprogramming library, is used to offload some of the work to the compiler, for example things like index mapping for slicing and multiplication.
* [boost unit](http://www.boost.org/doc/libs/1_58_0/libs/test/doc/html/index.html) : For the unit testing
  component of the library. This is not necessary of you aren't running the tests.

# Current Status

Currently the library is CPU only and is single-threaded as the development process has just begun. However, the library will be extended to include GPU functionality (with CUDA and probably also OpenCL) and multi-threading (and therefore multi-core CPU - probably with OpenMP and MPI).

# Building

To build the test suite which is provided with the library you will need two things installed: The Boost test libraries and the CUDA SDK (although this is not necessary for CPU only builds - see [Compiling](#compiling) below).

The following compilers have been tested:

* g++ version 4.9.1
* clang++ version 3.6.1
* nvcc 

## Nano 

You can get the nano library from here - [nano](https://github.com/robclu/nano) - it is a header only
library. By default it is installed to ```usr/include```. If you install it somewhere else make sure that it
is on your path so that ```tensor``` can find it.

## Boost

You can get the Boost test library from here - [Boost](http://www.boost.org/) - and follow the [Getting Started Guide](http://www.boost.org/doc/libs/1_59_0/more/getting_started/index.html) to install the libraries.

__Note:__ You only need the test library, and it is dynamically linked in the Makefile provided with the ```tensor``` library, so you should install it to allow dynamic linking (i.e install the test library and not just the ```.hpp``` file.

## CUDA

If you want to enable the GPU components of the library (for additional performance) then you will need to install the CUDA SDK (version 7 is used by ```tensor```). You can find the CUDA SDK here -[CUDA 7](https://developer.nvidia.com/cuda-downloads) - and follow the __Getting Started Guide__ provided on the same page below the download section.

__Note:__ If you do not have a GPU you can still use ```tensor``` - see below for compiling without GPU support.

## Compiling

For compiling, there are two 'categories', each with two options, giving a total of 4 options for compiling. The options are:

* GPU or CPU 
* Debug or Release

```Debug``` mode enables debugging support, while ```Release``` mode enables compiler optimizations.

The Makefile is provided in the ```tensor/``` (root) directory, so to compile the test suit, navigate to that directory. The test suite can then be built using any combination of the above categories, so 

```
make cpu_debug    # default (make all does the same thing)
make gpu_debug    # or
make cpu_release  # or 
make gpu_release  
```

The above commands will automatically run the test suite, and create an ```ftl_tests`` executable which can then be run using either of

```
./ftl_tests       # or
make run
```

# Known Issues

* When compiling with g++ there is an error for ```tensor_multiplication``` when accessing elements through
  the ```[]``` operator. The ```[]``` operator calls the ```calculate_value()``` function to get the value of
the ith element. This relies on the ```_x``` and ```_y``` constant reference variables. The problem is that
when compiled with g++, when the ```[]``` operator calls the ```calculate_value()``` function, the reference
variables are incorrect. There is no problem when compiling with clang though! I'm currently working on this.

# Usage 

The goal of *tensor* is to provide speed, and more importantly, tensor expressions which look in code as they
do mathematically, allowing the library to be simple to use scientifically. 
  
## Creating a tensor

To create a tensor (minimmallY, the data type and rank (number of dimensions) must be specified.

```.cpp
ftl::tensor<int, 2> A;          // Rank 2 tensor (A matrix)
```

There are then a number of ways to provide more information to the tensor. The size of the dimensions can be
initialized as follows

```.cpp
ftl::tensor<int, 3> A = {2, 2, 2};      // Rank 3 tensor with each dimension having a value of 2
                                        // Or equivalently, a 2x2 matrix with 2 pages
```

A tensor can also be given dimension sizes and data in the form of vectors, such as 

```.cpp
std::vector<size_t> dimension_sizes{ 2, 2 };
std::vector<int>    data{ 1, 2, 3, 4 };
 
ftl::tensor<int, 2> A(dimension_sizes, data);
```

__Note:__ The first dimension in a tensor is the vertical (column, or i) dimension, so a 2D tensor is stored column
major. The next dimension is then horizonal (rows, or j), followed by depth (pages, or z). This makes a 3D
space. The dimensions the repeat themselves (so vertical, horizontal, depth) but using blocks. Images will be
added for illustration.

Using the above as an example (for now) the rank 2 tensor with dimensions of 2x2 will look like 

```.cpp
1 3
2 4
```

and its memory layout will be 

```.cpp
1 2 3 4
```

## Initialization

Since it is inconvienient to set all the tensor elements for large system (such as weights in a neural
network), the tensor elements can be initialized with the elements uniformly distributed between a range.

```.cpp
ftl::tensor<float, 4> A = { 3, 3, 2, 2 };
 
// Initialize tensor with elements [0, 1]
initialize(A, 0, 1.0f);
```

## Operations

There are numerous operations for tensors, such as (currently)

* Multiplication
* Addition 
* Subtraction

### Multiplication

Currently tensors use Eienstein reduction for multiplication, which means that dimensions which are common to
both tensors are reduced, so given A and B (both 2x2 tensors), the following is an example of the reduction 

C_ik = A_ij * B_jk

So the common dimension is reduced. Using *tensor*, what you call the dimensions doesn't matter, just that the
dimensions to be reduced are called the same thing. Additionally, *tensor* provides index variables, through
the ```ftl::idx``` namespace. which allows the code to look as it would mathematically. For example

```.cpp
// Define namespace for indices
using namespace ftl::idx;

// Create 2 tensors (not providing data for previty
ftl::tensor<int, 2> A = { 3, 2 };       // 3 rows, 2 columns
ftl::tensor<int, 2> B = { 2, 3 };       // 2 rows, 3 columns

// This is an example of matrix multiplication and will 
// result in a rank 2 tensor with dimension sizes of 3 and 3
// so this is a 3x3 matrix
auto C = A(i, j) * B(j, k);             // C_ik = A_ij * B_jk
       
// Since the dimension names don't matter, this would be the same
// Although this doesn't look as appelaing
auto C = A(l, i) * B(i, j);             // C_lj = A_li * B_ij
```
