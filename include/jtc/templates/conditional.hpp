// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// conditional.hpp: Ternary operator template for type selection

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_CONDITIONAL_HPP
#define JTC_TEMPLATES_CONDITIONAL_HPP

namespace jtc {

/// Emulates std::conditional:
///   If B == true,  the conditional::type member will be TTrue
///   If B == false, the conditional::type member will be TFalse
template <bool B, typename TTrue, typename TFalse> struct conditional;

template <typename TTrue, typename TFalse> struct conditional<false, TTrue, TFalse> { using type = TFalse; };
template <typename TTrue, typename TFalse> struct conditional<true,  TTrue, TFalse> { using type = TTrue;  };

/// Alias for conditional<...>::type
template <bool B, typename TTrue, typename TFalse> using conditional_t = typename conditional<B, TTrue, TFalse>::type;

}  // namespace jtc

#endif