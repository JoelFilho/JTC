// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// make_signed_unsigned.hpp: defines make_signed and make_unsigned for the standard types

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_MAKE_SIGNED_UNSIGNED_HPP
#define JTC_TEMPLATES_MAKE_SIGNED_UNSIGNED_HPP

#include "conditional.hpp"
#include "cv_ref_traits.hpp"
#include "number_traits.hpp"
#include "type_map.hpp"

namespace jtc {

// Forward declaration of the implementation
// !is_same_v<T, char>() is used in both because char signedness is not defined.
namespace detail {
template <typename T, bool B = is_signed_v<T>()   && !is_same_v<T, char>()> struct make_signed_impl;
template <typename T, bool B = is_unsigned_v<T>() && !is_same_v<T, char>()> struct make_unsigned_impl;
}

//-------------------------------------------------------------------------------------------------
// make_signed and make_unsigned declarations
//-------------------------------------------------------------------------------------------------

template <typename T> struct make_unsigned   : detail::make_unsigned_impl<T> {};
template <typename T> using  make_unsigned_t = typename make_unsigned<T>::type;

template <typename T> struct make_signed   : detail::make_signed_impl<T> {};
template <typename T> using  make_signed_t = typename make_signed<T>::type;

//-------------------------------------------------------------------------------------------------
// make_signed and make_unsigned's implementation using a type_map
//-------------------------------------------------------------------------------------------------

namespace detail {

// Mapping from signed types to unsigned types
// Uses the linear search of type_map to implement specializations for char, where signedness is implementation-defined.
using unsigned_map = type_map<map_node<int, unsigned int>,              // Default mappings: [signed] int <-> unsigned int
                              map_node<short, unsigned short>,          // [signed] short [int] <-> unsigned short [int]
                              map_node<long, unsigned long>,            // And repetitions for all signed types
                              map_node<long long, unsigned long long>,  //   defined by the Standard. Except for char,
                              map_node<signed char, unsigned char>,     //   explicitly signed here.
                              map_node<char, unsigned char>,            // Fallback case for make_unsigned<char>
                              map_node<signed char, char>               // Fallback case for make_signed<char>
                              >;

// Mapping from unsigned to signed, by inverting unsigned_map
using signed_map = map_invert_t<unsigned_map>;

// Implementations
// If a type already fits the requirements, it's not changed.
// Otherwise, its type is transformed using the type appropriate map.
// In the case of char, make_signed always returns signed char and make_unsigned returns unsigned char,
//   regardless of char signedness.

template <typename T> struct make_unsigned_impl<T, true>  : make_type<T> {};
template <typename T> struct make_unsigned_impl<T, false> : make_type<copy_cv_t<T, map_get_t<unsigned_map, remove_cv_t<T>>>> {};

template <typename T> struct make_signed_impl<T, true>    : make_type<T> {};
template <typename T> struct make_signed_impl<T, false>   : make_type<copy_cv_t<T, map_get_t<signed_map, remove_cv_t<T>>>> {};

}  // namespace detail
}  // namespace jtc

//-------------------------------------------------------------------------------------------------
// Compile-time Tests
//-------------------------------------------------------------------------------------------------

#ifndef JTC_NO_TESTS

namespace jtc {
namespace tests {

// TODO

}  // namespace tests
}  // namespace jtc

#endif  // JTC_NO_TESTS

#endif