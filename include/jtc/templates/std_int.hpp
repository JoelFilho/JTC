// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// std_int.hpp: Emulates <cstdint>'s [u]int[N]_t, assuming CHAR_BIT=8
//              If CHAR_BIT != 8, for some reason, you must provide a <stdint.h> instead.

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_STD_INT_HPP
#define JTC_TEMPLATES_STD_INT_HPP

#include "integral_constant.hpp"
#include "number_traits.hpp"
#include "std_def.hpp"
#include "type_list.hpp"

namespace jtc {

// Implementation of the [u]int[N]_t types
namespace detail {

/// A type_list of Standard integral types, signed and unsigned
using number_types = type_list<int, unsigned int, long, unsigned long, long long, unsigned long long, signed char,
                               unsigned char, short, unsigned short>;

/// Type responsible for finding integers with specified size
///   Signed: Boolean value, indicating whether the type is signed
///   Size: Number of bytes of the required type
template <bool Signed, size_t Size>
struct integer_type_finder {
  /// Search operator: does T match signedness and size requirements?
  template <typename T>
  using match_operator = bool_constant<(Signed ? is_signed_v<T>() : is_unsigned_v<T>()) && (sizeof(T) == Size)>;
  /// Result of the search. See 'result_type' for details.
  using result = list_find_where<number_types, match_operator>;
};

/// External interface for type matching. Returns the 'type' member of the search result.
template <bool Signed, size_t Size>
using integer_type_match_t = typename integer_type_finder<Signed, Size>::result::type;

}  // namespace detail

//-------------------------------------------------------------------------------------------------
// Type definitions
//-------------------------------------------------------------------------------------------------

using int8_t  = detail::integer_type_match_t<true, 1>;
using int16_t = detail::integer_type_match_t<true, 2>;
using int32_t = detail::integer_type_match_t<true, 4>;
using int64_t = detail::integer_type_match_t<true, 8>;

using uint8_t  = detail::integer_type_match_t<false, 1>;
using uint16_t = detail::integer_type_match_t<false, 2>;
using uint32_t = detail::integer_type_match_t<false, 4>;
using uint64_t = detail::integer_type_match_t<false, 8>;

}  // namespace jtc

#endif