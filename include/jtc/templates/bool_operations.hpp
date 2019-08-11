// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// bool_operations.hpp: Defines bool operations for parameter packs.
//                      Assumes all types have a boolean 'value' member, like in bool_constant.

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_BOOL_OPERATIONS_HPP
#define JTC_TEMPLATES_BOOL_OPERATIONS_HPP

#include "integral_constant.hpp"
#include "type_list.hpp"

namespace jtc {

//-------------------------------------------------------------------------------------------------
// Binary and Unary Boolean Operators
//-------------------------------------------------------------------------------------------------

/// Defines the unary and binary boolean operators.
/// All types require a bool 'value' member in each of their operands.
namespace operators {

/// Unary NOT operator
template <typename Bool>
using not_op = bool_constant<!Bool::value>;

/// Binary AND operator
template <typename BoolA, typename BoolB>
using and_op = bool_constant<BoolA::value && BoolB::value>;

/// Binary OR operator
template <typename BoolA, typename BoolB>
using or_op = bool_constant<BoolA::value || BoolB::value>;

/// Binary XOR operator
template <typename BoolA, typename BoolB>
using xor_op = bool_constant<BoolA::value != BoolB::value>;

}  // namespace operators

//-------------------------------------------------------------------------------------------------
// Parameter pack boolean operators
//
// All operators assume all BoolTypes have a boolean 'value' member.
//-------------------------------------------------------------------------------------------------

/// Unary NOT operator
template <typename Bool>
using bool_not = operators::not_op<Bool>;

/// Value of the unary NOT operator
template <typename Bool>
inline constexpr bool bool_not_v() { return bool_not<Bool>::value; }

/// n-ary AND operator
template <typename... BoolTypes>
using bool_and = list_reduce_t<type_list<BoolTypes...>, operators::and_op>;

/// Value of the n-ary AND operator
template <typename... BoolTypes>
inline constexpr bool bool_and_v() { return bool_and<BoolTypes...>::value; }

/// n-ary OR operator
template <typename... BoolTypes>
using bool_or = list_reduce_t<type_list<BoolTypes...>, operators::or_op>;

/// Value of the n-ary OR operator
template <typename... BoolTypes>
inline constexpr bool bool_or_v() { return bool_or<BoolTypes...>::value; }

/// n-ary XOR operator
template <typename... BoolTypes>
using bool_xor = list_reduce_t<type_list<BoolTypes...>, operators::xor_op>;

/// Value of the n-ary XOR operator
template <typename... BoolTypes>
inline constexpr bool bool_xor_v() { return bool_xor<BoolTypes...>::value; }

}  // namespace jtc

//-------------------------------------------------------------------------------------------------
// Compile-time Tests
//-------------------------------------------------------------------------------------------------

#ifndef JTC_NO_TESTS

namespace jtc {
namespace tests {

/// Binary and unary operators truth table tests
struct bool_operators_test {
  // NOT
  static_assert(!jtc::operators::not_op<true_type>::value, "JTC test failed!");
  static_assert(jtc::operators::not_op<false_type>::value, "JTC test failed!");

  // AND
  static_assert(!jtc::operators::and_op<false_type, false_type>::value, "JTC test failed!");
  static_assert(!jtc::operators::and_op<false_type, true_type>::value, "JTC test failed!");
  static_assert(!jtc::operators::and_op<true_type, false_type>::value, "JTC test failed!");
  static_assert(jtc::operators::and_op<true_type, true_type>::value, "JTC test failed!");

  // OR
  static_assert(!jtc::operators::or_op<false_type, false_type>::value, "JTC test failed!");
  static_assert(jtc::operators::or_op<false_type, true_type>::value, "JTC test failed!");
  static_assert(jtc::operators::or_op<true_type, false_type>::value, "JTC test failed!");
  static_assert(jtc::operators::or_op<true_type, true_type>::value, "JTC test failed!");

  // XOR
  static_assert(!jtc::operators::xor_op<false_type, false_type>::value, "JTC test failed!");
  static_assert(jtc::operators::xor_op<false_type, true_type>::value, "JTC test failed!");
  static_assert(jtc::operators::xor_op<true_type, false_type>::value, "JTC test failed!");
  static_assert(!jtc::operators::xor_op<true_type, true_type>::value, "JTC test failed!");
};

/// Boolean operator pack tests
struct bool_operators_pack_test {
  // AND
  static_assert(!jtc::bool_and_v<false_type>(), "JTC test failed!");
  static_assert(jtc::bool_and_v<true_type>(), "JTC test failed!");
  static_assert(jtc::bool_and_v<true_type, true_type, true_type>(), "JTC test failed!");
  static_assert(!jtc::bool_and_v<true_type, true_type, false_type>(), "JTC test failed!");

  // OR
  static_assert(!jtc::bool_or_v<false_type>(), "JTC test failed!");
  static_assert(jtc::bool_or_v<true_type>(), "JTC test failed!");
  static_assert(jtc::bool_or_v<true_type, true_type, true_type>(), "JTC test failed!");
  static_assert(jtc::bool_or_v<true_type, true_type, false_type>(), "JTC test failed!");
  static_assert(!jtc::bool_or_v<false_type, false_type>(), "JTC test failed!");
  static_assert(!jtc::bool_or_v<false_type, false_type, false_type, false_type>(), "JTC test failed!");

  // XOR (i.e. odd number of trues)
  static_assert(!jtc::bool_xor_v<false_type>(), "JTC test failed!");
  static_assert(jtc::bool_xor_v<true_type>(), "JTC test failed!");
  static_assert(jtc::bool_xor_v<true_type, true_type, true_type>(), "JTC test failed!");
  static_assert(jtc::bool_xor_v<true_type, false_type, false_type>(), "JTC test failed!");
  static_assert(!jtc::bool_xor_v<false_type, false_type>(), "JTC test failed!");
  static_assert(jtc::bool_xor_v<true_type, true_type, true_type, false_type>(), "JTC test failed!");
  static_assert(!jtc::bool_xor_v<true_type, false_type, false_type, true_type>(), "JTC test failed!");
};

}  // namespace tests
}  // namespace jtc

#endif  // JTC_NO_TESTS

#endif