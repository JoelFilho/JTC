# Joel's Template Collection (JTC)

JTC is a header-only collection of C++11-compatible templates. It includes functions, classes, type traits and random metaprogramming helpers. JTC is primarily a personal project, developed as a learning experience, and it is shared with the hope of being useful. The main features and design goals of the project are:

1. **No C++ Standard Library dependencies**, making it a viable option for embedded development in platforms where a C++11 compiler is available, but shipped without STL headers (e.g. AVR GCC).
    - Functions and type traits available on the Standard Library are often added to JTC, as needed from my other projects. 
    - "Modernized" versions of the utilities are usually implemented, bringing some of the C++14 and C++17 functionality into C++11. 
2. **Modularity**: Most files have few dependencies between themselves, so they can be easily imported into different projects without using the whole collection.
3. **Readability**: Hopefully, the code is clean and commented well enough for it to help others' learning journeys, as it has been helping me understand better some of the ins and outs of C++.
4. **Static tests**: Wherever viable, the code includes simple `static_assert`-based tests, to guarantee functionality under your compiler.
    - This behavior can be disabled by defining the macro `JTC_NO_TESTS`, for cases where tests slow down compilation of multiple translation units.
5. **Boost License**, a permissive, GPL-compatible license, that does not require attribution on binary distributions.

## How to use the "library"

JTC is header-only and has no external dependencies, so you can:

* Copy the `include/jtc` folder into your project or just the desired files;
* Download the single-header version of the library and embed into your project; **(TODO)**
* Utilize this repository as a git submodule, then add `include` to your include path;
    * This folder can also be used as a CMake subdirectory. **(TODO)**
* Install it using CMake for whole-system availability. **(TODO)**

Requirements:

* A C++11-compliant compiler where the size of `char` is 8 bits.

## Copyright / License

Copyright © 2019 Joel P. C. Filho

This software is released under the Boost Software License - Version 1.0. Refer to [the License file](LICENSE.md) for details. 
