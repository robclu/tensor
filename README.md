*A fast c++ tensor library*

# Tensor

Tensor is a fast (well hopefully) c++ tensor library. It is designed with both speed and clearity of expression in mind. It it thus intended to provide high levels of performance but allow operations on tensors in the code to appear exactly as they do mathematically. 

[Template metaprogramming](https://en.wikipedia.org/wiki/Template_metaprogramming) is used to 'offload' any work which can be computed at compile time, to the compiler and [expression templates](https://en.wikipedia.org/wiki/Expression_templates) are used to achieve the translation of the mathematically expressed code to performant code.

Tests have been written using the [Boost Test library](http://www.boost.org/doc/libs/1_58_0/libs/test/doc/html/index.html) to verify the 'correctness' of all the implemented components. The tests also help to illustrate the usage of the various components of the library.

Please let me know, or just fix, any areas of the code which can be improved!

# Dependancies

Tensor uses the [nano](https://github.com/robclu/nano) template metaprogramming library to do offload some of the work to the compiler, for example things like index mapping for slicing and multiplication.

# Current Status

Currently the library is CPU only and is single-threaded as the development process has just begun. However, the library will be extended to include GPU functionality (with CUDA) and multi-threading (and therefore multi-core CPU - probably with OpenMP and MPI).

# Building

To build the test suite which is provided with the library you will need two things installed: The Boost test libraries and the CUDA SDK (although this is not necessary for CPU only builds - see [Compiling](#compiling) below).

The dollowing compilers have been tested:

* g++ version 4.9.1
* clang++ version 3.6.1
* nvcc 

## Boost

You can get the Boost test library from here - [Boost](http://www.boost.org/) - and follow the [Getting Started Guide](http://www.boost.org/doc/libs/1_59_0/more/getting_started/index.html) to install the libraries.

__Note:__ You only need the test library, and it is dynamically linked in the Makefile provided with the __ftl__ library, so you should install it to allow dynamic linking (i.e install the test library and not just the ```.hpp``` file.

## CUDA

If you want to enable the GPU components of the library (for additional performance) then you will need to install the CUDA SDK (version 7 is used by __ftl__). You can find the CUDA SDK here -[CUDA 7](https://developer.nvidia.com/cuda-downloads) - and follow the __Getting Started Guide__ provided on the same page below the download section.

__Note:__ If you do not have a GPU you can still use __ftl__ - see below for compiling without GPU support.

## Compiling

For compiling, there are two 'categories', each with two options, giving a total of 4 options for compiling. The options are:

* GPU or CPU 
* Debug or Release

```Debug``` mode enables debugging support, while ```Release``` mode enables compiler optimizations.

The Makefile is provided in the ```ftl/include``` directory, so to compile the test suit, navigate to that directory. The test suite can then be built using any combination of the above categories, so 

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
