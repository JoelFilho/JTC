// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// sfinae_types.hpp: Defines C++17's SFINAE helper void_t, and a supertype of it, sfinae_t

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_SFINAE_TYPES_HPP
#define JTC_TEMPLATES_SFINAE_TYPES_HPP

namespace jtc {

// Implementation helper
namespace detail {
template <typename T, typename...>
struct sfinae_type {
  using type = T;
};
}  // namespace detail

/// Extends the Standard's void_t to any type T.
/// During substitution, it resolves to T if T and Args are valid types.
template <typename T, typename... Args>
using sfinae_t = typename detail::sfinae_type<T, Args...>::type;

/// Emulates the Standard's void_t utility
template <typename... Args>
using void_t = sfinae_t<void, Args...>;

}  // namespace jtc

#endif