// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// are_same.hpp: A helper for applying is_same to all items in a parameter pack

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_ARE_SAME_HPP
#define JTC_TEMPLATES_ARE_SAME_HPP

#include "bool_operations.hpp"
#include "is_same.hpp"

namespace jtc {

/// Defines whether all types in a parameter pack are the same
template <typename T, typename... Ts> struct are_same    : bool_and<is_same<T, Ts>...> {};
template <typename T>                 struct are_same<T> : true_type {};

/// Helper function to acquire the 'value' member of are_same
/// Returns whether all template parameters are the same
template <typename... Ts>
inline constexpr bool are_same_v() { return are_same<Ts...>::value; }

}  // namespace jtc

//-------------------------------------------------------------------------------------------------
// Compile-time Tests
//-------------------------------------------------------------------------------------------------

#ifndef JTC_NO_TESTS

namespace jtc {
namespace tests {

struct are_same_tests {
  // Single type
  static_assert(jtc::are_same_v<int>(), "JTC test failed!");
  static_assert(jtc::are_same_v<void>(), "JTC test failed!");

  // Multiple (same) types
  static_assert(jtc::are_same_v<int, signed int>(), "JTC test failed!");
  static_assert(jtc::are_same_v<short, short int, signed short, signed short int>(), "JTC test failed!");

  // Non-equal types
  static_assert(!jtc::are_same_v<int, int, float>(), "JTC test failed!");
  static_assert(!jtc::are_same_v<int, float, int>(), "JTC test failed!");
  static_assert(!jtc::are_same_v<float, int, int>(), "JTC test failed!");
};

}  // namespace tests
}  // namespace jtc

#endif  // JTC_NO_TESTS

#endif