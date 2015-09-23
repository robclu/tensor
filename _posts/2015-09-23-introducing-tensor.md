---
layout: page 
title: Introducing Tensor 
---  
 
Tensor is a c++ expression template library. It is designed with both speed and clarity of expression in mind. It is thus intended to provide high levels of performance but allow operations on tensors in the code to appear exactly as they do mathematically.

Template metaprogramming is used to 'offload' any work which can be computed at compile time, to the compiler and expression templates are used to achieve the translation of the mathematically expressed code to high performance code.

The long term goal is to develop something along the lines of the tensor library in the python theano libray, but with support for any rank tensors with both CPU and GPU functionality.

Tensor is written by [Rob Clucas](https://robclu.github.io) and is released under the [GNU GPL V2.0](http://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html).
 
## Why Tensor?

----

Tensor provides a lot of flexibility, making it suitable for numrous situations. The two main areas of
flexibility:

* __Container type:__ Tensor provides both static and dynamic containers. If the size of each of the
  dimensions of the tensor is known, a static container can be used which will improve performance, otherwise
a dynamic tensor can be used. 
* __Device type:__ Tensor provides (will provide) support for both CPU and GPU devices, CUDA will be used for
  the GPU implementations, and (most probably) Intel TBB will be used for multi-threaded CPU implementations.

## Documentation 

The automatically generated documentation from the code comments (using Doxygen) can be found at : [API documentation](/tensor/documentation).

## Installation 

Information regarding installation can be found at [installation](/tensor/installation) or through the link in the sidebar.

## Examples

Tensor is still under development, however, examples of the latest functionality can be found at
[examples](/tensor/examples).

Currently only the CPU implementations are supported. I will update the status and the examples as additional
functionality is added.

Suggestions for additional functionality are welcomed.

## Contact

Feel free to drop me an email at [robjclucas@gmail.com](mailto:robjclucas@gmail.com) with any comments or
suggestions.





