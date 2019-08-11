// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// number_traits.hpp: Type traits for numerical types

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_NUMBER_TRAITS_HPP
#define JTC_TEMPLATES_NUMBER_TRAITS_HPP

#include "cv_ref_traits.hpp"
#include "enable_if.hpp"
#include "integral_constant.hpp"
#include "type_list.hpp"

namespace jtc {

// Implementation of is_integral and is_float using type_list:
//  - All C++11's standard integral and floating-point types are stored in their respective lists;
//  - Before searching, the traits remove the cv-qualifiers from the types;
//  - The result is a bool_constant indicating whether the type is on one of these lists.
namespace detail {
using integers_list = type_list<char, signed char, unsigned char, bool, short, unsigned short, int, unsigned int, long,
                                unsigned long, long long, unsigned long long, char16_t, char32_t, wchar_t>;
using float_list = type_list<float, double, long double>;
}  // namespace detail

//-------------------------------------------------------------------------------------------------
// is_integral
//-------------------------------------------------------------------------------------------------

template <typename T>
struct is_integral : bool_constant<list_has_type<detail::integers_list, remove_cv_t<T>>()> {};

template <typename T>
inline constexpr bool is_integral_v() noexcept {
  return is_integral<T>::value;
}

//-------------------------------------------------------------------------------------------------
// is_floating_point
//-------------------------------------------------------------------------------------------------

template <typename T>
struct is_floating_point : bool_constant<list_has_type<detail::float_list, remove_cv_t<T>>()> {};

template <typename T>
inline constexpr bool is_floating_point_v() noexcept {
  return is_floating_point<T>::value;
}

//-------------------------------------------------------------------------------------------------
// is_arithmetic
//-------------------------------------------------------------------------------------------------

template <typename T>
struct is_arithmetic : bool_constant<is_floating_point_v<T>() || is_integral_v<T>()> {};

template <typename T>
inline constexpr bool is_arithmetic_v() noexcept {
  return is_arithmetic<T>::value;
}

//-------------------------------------------------------------------------------------------------
// is_signed
//-------------------------------------------------------------------------------------------------

// is_signed implementation:
//  - If the parameter is a number:
//    - It's bool_constant<true>, if T(-1) is negative
//    - It's bool_constant<false>, otherwise.
//  - Otherwise, it's bool_constant<false>.
namespace detail {
template <typename T, bool = is_arithmetic_v<T>()>
struct is_signed_impl : bool_constant<(T(0) > T(-1))> {};

template <typename T>
struct is_signed_impl<T, false> : false_type {};
}  // namespace detail

template <typename T>
struct is_signed : bool_constant<detail::is_signed_impl<T>::value> {};

template <typename T>
inline constexpr bool is_signed_v() noexcept {
  return is_signed<T>::value;
}

//-------------------------------------------------------------------------------------------------
// is_unsigned
//-------------------------------------------------------------------------------------------------

// Similar implementation to is_signed.
// Not mutually exclusive, because a type can be non-numeric, i.e. neither signed nor unsigned.
namespace detail {
template <typename T, bool = is_arithmetic_v<T>()>
struct is_unsigned_impl : bool_constant<(T(0) < T(-1))> {};

template <typename T>
struct is_unsigned_impl<T, false> : false_type {};
}  // namespace detail

template <typename T>
struct is_unsigned : bool_constant<detail::is_unsigned_impl<T>::value> {};

template <typename T>
inline constexpr bool is_unsigned_v() noexcept {
  return is_unsigned<T>::value;
}

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