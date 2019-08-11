// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// integer_sequence.hpp: emulates C++14's std::integer_sequence

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_INTEGER_SEQUENCE_HPP
#define JTC_TEMPLATES_INTEGER_SEQUENCE_HPP

#include "std_def.hpp"

namespace jtc {

// Forward declaration of the implementation
namespace detail { template <typename T, T N> struct integer_sequence_impl; }

//-------------------------------------------------------------------------------------------------
// integer_sequence and helpers
//-------------------------------------------------------------------------------------------------

/// A sequence of integers, "stored" in the Ns parameters
template <typename T, T... Ns>
struct integer_sequence {
  /// Type of the
  using value_type = T;

  /// Size of the sequence
  constexpr static size_t size() { return sizeof...(Ns); }
};

/// Helper to create an integer sequence of N elements, from 0 to N-1
template <typename T, T N> using make_integer_sequence = typename detail::integer_sequence_impl<T, N>::type;

/// Alias type to integer_sequence, used for indexes
template <size_t... Ns>    using index_sequence = integer_sequence<size_t, Ns...>;

/// Helper to create a list of indexes, from 0 to N-1
template <size_t N>        using make_index_sequence   = make_integer_sequence<size_t, N>;

//-------------------------------------------------------------------------------------------------
// integer_sequence implementation. O(N), but with O(log(N)) recursive calls
//-------------------------------------------------------------------------------------------------

namespace detail {

// Helper struct to build the sequences
template <typename T, T... Ns>
struct integer_sequence_type { using type = integer_sequence<T, Ns...>; };

// Concatenates two integer sequences as a integer_sequence_type
template <typename T1, typename T2>
struct concat;

template <typename T, T... N1s, T... N2s>
struct concat<integer_sequence<T, N1s...>, integer_sequence<T, N2s...>> : integer_sequence_type<T, N1s..., N2s...> {};

// Range type. Makes an integer_sequence from N0 to N1.
template <typename T, T N0, T N1>
struct integer_sequence_range;

template <typename T, T N0, T N1>
using integer_sequence_range_t = typename integer_sequence_range<T, N0, N1>::type;

// Divide-and-conquer approach: Divides the range in two, builds the sequences recursively, then concatenates
template <typename T, T N0, T N1>
struct integer_sequence_range
    : concat<integer_sequence_range_t<T, N0, (N1 + N0) / 2>, integer_sequence_range_t<T, (N1 + N0) / 2 + 1, N1>> {};

// Recursion stop condition: single integer -> list with 1 item
template <typename T, T N> struct integer_sequence_range<T, N, N> : integer_sequence_type<T, N> {};

// The integer_sequence implementation: make the range from 0 to N-1
template <typename T, T N> struct integer_sequence_impl : integer_sequence_range<T, 0, N - 1> {};

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