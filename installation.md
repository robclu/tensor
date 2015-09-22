---
layout: page
title: Installation
---

Nano is a header only library, so to use it you just need to include the header file:

```cpp
#include "nano/nano.hpp"
```

so long as the dirctory in which the nano folder is installed is in your ```PATH```. If it is not in your
path, to will need to give the compiler the directory in which the nano headers are found, like:

```
-I/path/to/nano/
```

A Makefile is provided to install nano to ```/usr/local``` by default (all this does is move the nano folder to 
```/usr/local``` which you can change by modifying the ```INSTALL_DIR``` variable in the Makefile to the desired
 path). 

You must then add the directory to the ```PATH``` (ideally add this to your ```~/.bashrc```):

```
export PATH=<INSTALL_DIR>:$PATH
```

Once the Makefile is setup, nano can be __installed__ with:

```
sudo make install
```

You can __uninstall__ nano as follows:

```
sudo make uninstall
```

## Compilers

Nano has been tested with the following compilers on ubuntu 15.04:

* g++ - version 4.9.1
* clang++ - version 3.6.1

I haven't tested it on Windows yet -- I will do a test shortly!

## Tests

A test file is provided to ensure that all the functionality is working correctly.
To run the test file you'll need to install the boost test library from [Boost](http://www.boost.org/) and 
(the test file dynamically links the test library, so you'll actually have to install the library and not 
just include the header file).

With Boost.Test and nano installed you can run the tests with:

```
make                    # builds then runs
                        # or
make build_and_run      # builds then runs
```

or by

```
make build              # only builds
./nano_test_suite       
```
