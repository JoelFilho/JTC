// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// move_forward.hpp: C++'s move and forward functions for perfect forwarding.

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_MOVE_FORWARD_HPP
#define JTC_TEMPLATES_MOVE_FORWARD_HPP

#include "cv_ref_traits.hpp"

namespace jtc {

/// C++14's std::forward implementation
/// (r-value reference specialization)
template <typename T>
constexpr T&& forward(remove_reference_t<T>&& t) noexcept {
  return static_cast<T&&>(t);
}

/// C++14's std::forward implementation
/// (l-value reference specialization)
template <typename T>
constexpr T&& forward(remove_reference_t<T>& t) noexcept {
  return static_cast<T&&>(t);
}

/// C++14's std::move implementation
template <typename T>
constexpr auto move(T&& t) noexcept -> remove_reference_t<T>&& {
  return static_cast<remove_reference_t<T>&&>(t);
}

}  // namespace jtc

#endif