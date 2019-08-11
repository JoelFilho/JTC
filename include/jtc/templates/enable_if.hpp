// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// enable_if.hpp: Defines the enable_if utility from the Standard

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_ENABLE_IF_HPP
#define JTC_TEMPLATES_ENABLE_IF_HPP

#include "make_type.hpp"

namespace jtc {

/// Emulates std::enable_if:
///   If B == true, it has a member type 'type' defined as T
///   Otherwise, there's no member type
template <bool B, typename T = void> struct enable_if {};
template <typename T>                struct enable_if<true, T> : make_type<T> {};

/// Alias for the 'type' member of enable_if
template <bool B, typename T = void> using  enable_if_t = typename enable_if<B, T>::type;

}  // namespace jtc

#endif