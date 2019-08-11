// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// result_type.hpp: A type for search query results

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_RESULT_TYPE_HPP
#define JTC_TEMPLATES_RESULT_TYPE_HPP

namespace jtc {

/// A type for compile-time search query results.
/// See the specializations for details.
/// For usage examples, see 'type_list' and 'type_map' search implementations.
template <bool B, typename T = void>
struct result_type;

/// Result type specialization for unsuccesful queries
/// Member 'value' indicates the unsuccessful result.
/// Trying to access the 'type' member causes a substitution error and can be used in SFINAE.
template <typename T>
struct result_type<false, T> {
  constexpr static bool value = false;
};

/// "Found" result type specialization.
/// Member 'value' indicates it was found.
/// Member 'type' indicates the type found.
template <typename T>
struct result_type<true, T> {
  constexpr static bool value = true;
  using type = T;
};
}  // namespace jtc

#endif