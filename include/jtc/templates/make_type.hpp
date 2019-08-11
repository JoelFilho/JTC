// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// make_type.hpp: Helper to increase readability of implementations by reducing boilerplate.
//                Alternatively, it also defines C++20's type_identity for compatibility.

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_MAKE_TYPE_HPP
#define JTC_TEMPLATES_MAKE_TYPE_HPP

namespace jtc {

/// Helper to avoid '{using type = T;}' boilerplate.
/// Usage: inherit from it, for a specific T.
template <typename T>
struct make_type {
  using type = T;
};

/// C++20's type_identity, same as this library's make_type
template <typename T> using type_identity   = make_type<T>;
/// Alias for type_identity<T>::type
template <typename T> using type_identity_t = typename make_type<T>::type;

}  // namespace jtc

#endif