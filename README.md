# PPMIO

Lei Mao

## Introduction

PPM format is an uncompressed image format. Because PPM format images are the easiest format to read and write, they have been widely used in C/C++ program unit tests to verify the algorithms used in the program are correct. To make it easier to read and manipulate PPM images in C/C++, PPMIO was implemented in the repository.

PPMIO is a simple PPM image C++ I/O library that does not rely on any non-standard external libraries. It supports reading PPM RGB images to `uint8_t` array, and write `uint8_t` array to images. Note that the PPM image layout format is `HWC`.


## Dependencies

* CMake 3.0.0+
* Valgrind 3.13.0 (Optional)

## Files

```
.
├── CMakeLists.txt
├── libs
│   ├── CMakeLists.txt
│   ├── ppm_io.cpp
│   └── ppm_io.h
├── LICENSE.md
├── ppm_io_demo.cpp
├── README.md
└── samples
    ├── giraffe.jpg
    ├── giraffe.ppm
    ├── giraffe_replicated.ppm
    ├── kangaroo.jpg
    ├── kangaroo.ppm
    ├── kangaroo_replicated.ppm
    └── README.md
```


## Usages

### Read PPM Image From File

The library will automatically determine if the PPM image is `P3` ASCII or `P6` binary. The method returns 0 if successful, 1 if not. The library only supports PPM RGB images whose pixel scale is 0 to 255.

```cpp
#include "ppm_io.h"

PPM ppmIn;
int status;
std::string inFilepath = './imageIn.ppm'
status = ppmIn.read(inFilepath);
```

### Save PPM Image to File

```cpp
PPM ppmOut = ppmIn;
std::string outFilepath = './imageOut.ppm'
// Switch between P3 and P6
ppmOut.setBinary(true);
status = ppmOut.write(outFilepath);
```

### Get Image Data

```cpp
// Get image height
ppmIn.getH();
// Get image width
ppmIn.getW();
// Get image handler
uint8_t * pImage = ppm.getImageHandler();
```

### More Advanced Usages

Please check the header file `ppm_io.h`.


## Demo

### Read and Write PPM Image

`giraffe_p3.ppm` and `portrait_p3_comment.ppm` are `P3` PPM,  and `kangaroo_p6.ppm` and `water-mill_p6_comment.ppm` are a `P6` PPM. In addition, `portrait_p3_comment.ppm` and `water-mill_p6_comment.ppm` contain addition comments in PPM file.

PPM images were read, saved and checked equivalence of input and output to make sure the library works correctly.

```bash
$ mkdir -p build
$ cd build
$ cmake ..
$ make
$ ./ppm_io_demo ../samples/giraffe_p3.ppm ../samples/giraffe_p3_replicated.ppm 
Reading PPM images from ../samples/giraffe_p3.ppm...
Reading PPM image successful.
Testing copy constructor......
Writing PPM images to ../samples/giraffe_p3_replicated.ppm...
Writing PPM image successful.
Testing assign operator...
Writing PPM images to ../samples/giraffe_p3_replicated.ppm...
Writing PPM image successful.
PPM image in and out are the same.

$ ./ppm_io_demo ../samples/kangaroo_p6.ppm ../samples/kangaroo_p6_replicated.ppm 
Reading PPM images from ../samples/kangaroo_p6.ppm...
Reading PPM image successful.
Testing copy constructor......
Writing PPM images to ../samples/kangaroo_p6_replicated.ppm...
Writing PPM image successful.
Testing assign operator...
Writing PPM images to ../samples/kangaroo_p6_replicated.ppm...
Writing PPM image successful.
PPM image in and out are the same.


$ ./ppm_io_demo ../samples/portrait_p3_comment.ppm ../samples/portrait_p3_comment_replicated.ppm 
Reading PPM images from ../samples/portrait_p3_comment.ppm...
Reading PPM image successful.
Testing copy constructor......
Writing PPM images to ../samples/portrait_p3_comment_replicated.ppm...
Writing PPM image successful.
Testing assign operator...
Writing PPM images to ../samples/portrait_p3_comment_replicated.ppm...
Writing PPM image successful.
PPM image in and out are the same.

$ ./ppm_io_demo ../samples/water-mill_p6_comment.ppm ../samples/water-mill_p6_comment_replicated.ppm
Reading PPM images from ../samples/water-mill_p6_comment.ppm...
Reading PPM image successful.
Testing copy constructor......
Writing PPM images to ../samples/water-mill_p6_comment_replicated.ppm...
Writing PPM image successful.
Testing assign operator...
Writing PPM images to ../samples/water-mill_p6_comment_replicated.ppm...
Writing PPM image successful.
PPM image in and out are the same.

```

### Memory Leak Test

Additionally, all the runtimes above have passed Valgrind memory leak check. For example

```bash
$ valgrind --leak-check=yes ./ppm_io_demo ../samples/water-mill_p6_comment.ppm ../samples/water-mill_p6_comment_replicated.ppm
==19759== Memcheck, a memory error detector
==19759== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==19759== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==19759== Command: ./ppm_io_demo ../samples/water-mill_p6_comment.ppm ../samples/water-mill_p6_comment_replicated.ppm
==19759== 
Reading PPM images from ../samples/water-mill_p6_comment.ppm...
Reading PPM image successful.
Testing copy constructor......
Writing PPM images to ../samples/water-mill_p6_comment_replicated.ppm...
Writing PPM image successful.
Testing assign operator...
Writing PPM images to ../samples/water-mill_p6_comment_replicated.ppm...
Writing PPM image successful.
PPM image in and out are the same.
==19759== 
==19759== HEAP SUMMARY:
==19759==     in use at exit: 0 bytes in 0 blocks
==19759==   total heap usage: 22 allocs, 22 frees, 2,873,844 bytes allocated
==19759== 
==19759== All heap blocks were freed -- no leaks are possible
==19759== 
==19759== For counts of detected and suppressed errors, rerun with: -v
==19759== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```