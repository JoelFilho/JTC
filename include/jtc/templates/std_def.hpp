// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// std_def.hpp: A collection of types from <cstddef>

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_STD_DEF_HPP
#define JTC_TEMPLATES_STD_DEF_HPP

namespace jtc {

/// Unsigned type for addresses/indexes
/// See C/C++ reference for the type for more information.
using size_t = decltype(sizeof(int));

/// Type of nullptr
using nullptr_t = decltype(nullptr);

}  // namespace jtc

#endif