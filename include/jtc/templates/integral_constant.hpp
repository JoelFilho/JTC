// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// integral_constant.hpp: Defines integral_constant and bool_constant

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_INTEGRAL_CONSTANT_HPP
#define JTC_TEMPLATES_INTEGRAL_CONSTANT_HPP

namespace jtc {

//-------------------------------------------------------------------------------------------------
// integral_constant
//-------------------------------------------------------------------------------------------------

/// Emulates C++14's std::integral_constant.
/// Stores a Value of type Integer in compile time.
template <typename Integer, Integer Value>
struct integral_constant {
  /// Alias to this class's own type
  using type = integral_constant;
  /// Alias to the integral type it stores
  using value_type = Integer;
  /// Value of the integral type
  constexpr static Integer value = Value;
  /// Value type for easier casting
  constexpr operator value_type() const noexcept { return value; }
  /// Casting to value type through () call
  constexpr value_type operator()() const noexcept { return value; }
};

//-------------------------------------------------------------------------------------------------
// Boolean Helpers: bool_constant, true_type and false_type
//-------------------------------------------------------------------------------------------------

/// Helper alias of integral_constant, based on C++17's std::bool_constant
template <bool B> using bool_constant = integral_constant<bool, B>;

/// Emulates std::true_type
using true_type = bool_constant<true>;

/// Emulates std::false_type
using false_type = bool_constant<false>;

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