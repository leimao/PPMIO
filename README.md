# PPMIO

Lei Mao

## Introduction

PPM format is an uncompressed image format. Because PPM format images are the easiest format to read and write, they have been widely used in C/C++ program unit tests to verify the algorithms used in the program are correct. To make it easier to read and manipulate PPM images in C/C++, PPMIO was implemented in the repository.

PPMIO is a simple PPM image C++ I/O library that does not rely on any non-standard external libraries. It supports reading PPM RGB images to `uint8_t` array, and write `uint8_t` array to images. Note that the PPM image layout format is `HWC`.


## Dependencies

* CMake 3.0.0+
* Valgrind 3.13.0 (Optional)

## Usages

### Read PPM Image From File

The library will automatically determine if the PPM image is `P3` ASCII or `P6` binary. The method returns 0 if successful, 1 if not. The library only supports PPM RGB images whose pixel scale is 0 to 255.

```cpp
PPM ppmIn;
int status;
std::string filepath = './image.ppm'
status = ppmIn.read(filepath);
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

`giraffe.ppm` is `P3` PPM and `kangaroo.ppm` is a `P6` PPM.

```bash
$ mkdir -p build
$ cd build
$ cmake ..
$ make
$ ./ppm_io_demo ../samples/giraffe.ppm ../samples/giraffe_replicated.ppm
Reading PPM images from ../samples/giraffe.ppm...
Reading PPM image successful.
Testing copy constructor......
Writing PPM images to ../samples/giraffe_replicated.ppm...
Writing PPM image successful.
Testing assign operator...
Writing PPM images to ../samples/giraffe_replicated.ppm...
Writing PPM image successful.
$ ./ppm_io_demo ../samples/kangaroo.ppm ../samples/kangaroo_replicated.ppm
Reading PPM images from ../samples/kangaroo.ppm...
Reading PPM image successful.
Testing copy constructor......
Writing PPM images to ../samples/kangaroo_replicated.ppm...
Writing PPM image successful.
Testing assign operator...
Writing PPM images to ../samples/kangaroo_replicated.ppm...
Writing PPM image successful.
```

| PPM Input | PPM Output | 
|:-------------------------:|:-------------------------:|
|![](samples/giraffe.ppm) | ![](samples/giraffe_replicated.ppm) | 
|![](samples/kangaroo.ppm) | ![](samples/kangaroo_replicated.ppm) | 



## Memory Leak Test

Additionally, Valgrind was employed to verify that there is no memory leak issue.

```bash
$ valgrind --leak-check=yes ./ppm_io_demo ../samples/giraffe.ppm ../samples/giraffe_replicated.ppm
==701== Memcheck, a memory error detector
==701== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==701== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==701== Command: ./ppm_io_demo ../samples/giraffe.ppm ../samples/giraffe_replicated.ppm
==701== 
Reading PPM images from ../samples/giraffe.ppm...
Reading PPM image successful.
Testing copy constructor......
Writing PPM images to ../samples/giraffe_replicated.ppm...
Writing PPM image successful.
Testing assign operator...
Writing PPM images to ../samples/giraffe_replicated.ppm...
Writing PPM image successful.
==701== 
==701== HEAP SUMMARY:
==701==     in use at exit: 0 bytes in 0 blocks
==701==   total heap usage: 17 allocs, 17 frees, 2,479,008 bytes allocated
==701== 
==701== All heap blocks were freed -- no leaks are possible
==701== 
==701== For counts of detected and suppressed errors, rerun with: -v
==701== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
$ valgrind --leak-check=yes ./ppm_io_demo ../samples/kangaroo.ppm ../samples/kangaroo_replicated.ppm
==621== Memcheck, a memory error detector
==621== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==621== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==621== Command: ./ppm_io_demo ../samples/kangaroo.ppm ../samples/kangaroo_replicated.ppm
==621== 
Reading PPM images from ../samples/kangaroo.ppm...
Reading PPM image successful.
Testing copy constructor......
Writing PPM images to ../samples/kangaroo_replicated.ppm...
Writing PPM image successful.
Testing assign operator...
Writing PPM images to ../samples/kangaroo_replicated.ppm...
Writing PPM image successful.
==621== 
==621== HEAP SUMMARY:
==621==     in use at exit: 0 bytes in 0 blocks
==621==   total heap usage: 17 allocs, 17 frees, 2,553,893 bytes allocated
==621== 
==621== All heap blocks were freed -- no leaks are possible
==621== 
==621== For counts of detected and suppressed errors, rerun with: -v
==621== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```