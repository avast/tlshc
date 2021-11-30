[![CMake](https://github.com/avast/tlshc/actions/workflows/cmake.yml/badge.svg?branch=main&event=push)](https://github.com/avast/tlshc/actions/workflows/cmake.yml)

# TLSHC

This repository ports the original [TLSH](https://github.com/trendmicro/tlsh) C++ project into C by removing any C++ dependency and creating a C interface. Most of the code of the original repository was kept to not introduce any possible bugs and differences from the original implementation.


## Use of the library
Integrating the library is very easy through CMake. If you installed the library into a standard installation location of your system (e.g. `/usr`, `/usr/local`), all you need to do in order to use its components is:

```cmake
find_package(tlshc REQUIRED)

target_link_libraries(your-project
    PUBLIC 
        tlshc
      [...]
)
```

If your library is in different location, you can pass the path to your CMake `-Dtlshc_DIR=<path>` or set a `CMAKE_PREFIX_PATH`.

A trivial example of library use can be found in [here](https://github.com/avast/tlshc/blob/main/example).

## Build, Installation and Testing

Edit CMakeLists.txt to build TLSH with different options.

- **TLSH_BUCKETS**: determines using 128 or 256 buckets use the default 128 buckets unless you are an expert and know you need 256 buckets
- **TLSH_CHECKSUM_1B**: determines checksum length, longer means less collision use the default 1 byte unless you are an expert and know you need a larger checksum

### Requirements

* C compiler 
* [CMake](https://cmake.org/) (version >= 3.14)

### Build and Installation
* Clone the repository:
  * `git clone https://github.com/avast/tlshc/`
* Linux and MacOS:
  * `cd tlshc`
  * `mkdir build && cd build`
  * `cmake .. -DCMAKE_INSTALL_PREFIX=<path>`
  * `make install`
* Windows:
  * `cd tlshc`
  * `mkdir build && cd build`
  * `cmake .. -DCMAKE_INSTALL_PREFIX=<path>`
  * `cmake --build . --config Debug --target install`

### Testing
There are few simple test vectors created with the original implementation to verify the correctness of the library. Tests can be built using `-DBUILD_TESTS=ON` CMake option.

To run the tests go to the `build/` folder and run:
```sh
ctest -V
```

## License

See the [LICENSE](https://github.com/avast/tlshc/blob/main/LICENSE) file for more details.
