// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// declval.hpp: The declval utility

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_DECLVAL_HPP
#define JTC_TEMPLATES_DECLVAL_HPP

#include "cv_ref_traits.hpp"

namespace jtc {

/// Emulates std::declval.
/// The return type should only be use in unevaluated contexts, such as decltype.
template <typename T> auto declval() noexcept -> add_rvalue_reference_t<T>;

}  // namespace jtc

#endif