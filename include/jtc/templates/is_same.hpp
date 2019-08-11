// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// is_same.hpp: Defines is_same, as defined by the Standard.

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_IS_SAME_HPP
#define JTC_TEMPLATES_IS_SAME_HPP

#include "integral_constant.hpp"

namespace jtc {

/// Defines whether T1 and T2 are the same type and stores the result on the 'value' member
template <typename T1, typename T2> struct is_same       : false_type {};
template <typename T>               struct is_same<T, T> : true_type  {};

/// Helper function to acquire the 'value' member of is_same
/// Returns whether T1 and T2 are the same type
template <typename T1, typename T2>
inline constexpr bool is_same_v() { return is_same<T1, T2>::value; }

}  // namespace jtc

#endif