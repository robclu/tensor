---
layout: post
title: Tensor Declarations
---

This page provides examples of the available tensor types and their usage.

# Dynamic Tensors

Dynamic tensors are tensors for which the size, and hence the sizes of the dimensions, are not known. This
lack of information requires using a vector so that the container can be dynamically allocated. This
flexibility comes at the cost of performance.

A dynamic tensor can be declared using either the general tensor interface, providing type for the tensor and
the device to use for computation, for example
 
```cpp
// Declare a CPU tensor with integer elements
ftl::Tensor<int, ftl::CPU> cpu_tensor;

// Declare a GPU tensor with floating point elements
ftl::Tensor<float, ftl::GPU> gpu_tensor;
```

Additionally, tensor defines type aliases for ```CPU``` tensors, so a dynamic CPU tensor can be declared as
follows

```cpp
// Declare a dynamic CPU tensor with integer elements
ftl::DynamicTensorCpu<int>
```

# Static Tensors

Static tensors should be used when performance is critial and when the size of the dimensions is known when
the tensor is created. The dimension sizes must be passed as template parameters. This choice was made to
allow a lot of the computation for index offsetting to be done at compile-time, greatly improving performance.
A static tensor can be declared using the general tensor interface as follows

```cpp
// Declare a 2 dimensional (rank 2) cpu static tensor with integer elements
// This example is the equivalent of a 4x4 matrix
ftl::Tensor<int, ftl::CPU,
            4,                  // Size of the first dimension
            4                   // Size of the second dimension
            > cpu_tensor;   
```

As for dynamic tensors, tensor defines a type alias for static CPU tensors. The same static tensor as above
can also be created as follows

```cpp
// Declare a rank 2 static cpu tensor 
// This is also a 4x4 matrix
ftl::StaticTensorCpu<int, 4, 4> cpu_tensor;
```

A particularly important part of tensor is that the number of dimensions which a tensor may have is unbound,
so a 5 dimensional static tensor could be created as follows

```cpp
ftl::StaticTensorCpu<float, 2, 3, 4, 2, 2> rank_five_tensor;
```

You can also provide the data for the static tensor to the constructor, such as 

```cpp
ftl::StaticTensorCpu<int, 2, 2> A{ { 1, 2, 3, 4 } };
```

# Initialization 

See the page on [initialization](/tensor/usage/initialization) for how tensors can be initialized efficiently.

# Memory Layout

As tensors support N dimensions, the memory layout becomes complex, thus a dedicated page is provided for a
detailed explanation, see [memory layout](/tensor/usage/memorylayout/).