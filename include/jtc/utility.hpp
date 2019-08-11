// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// utility.hpp: Generic Programming helpers

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_UTILITY_HPP
#define JTC_UTILITY_HPP

//-------------------------------------------------------------------------------------------------
// General helpers
//-------------------------------------------------------------------------------------------------

// Emulates std::move (xvalue cast) and std::forward (perfect forwarding helper)
#include "templates/move_forward.hpp"

// Emulates C++'s declval helper function
#include "templates/declval.hpp"

//-------------------------------------------------------------------------------------------------
// Template Metaprogramming Utilities
//-------------------------------------------------------------------------------------------------

// Emulates C++14's integer_sequence utility
#include "templates/integer_sequence.hpp"

// Defines a type for search queries result
#include "templates/result_type.hpp"

// List of types, with search and map/reduce operations
#include "templates/type_list.hpp"

// Map of types, for easy 1-to-1 type matching
#include "templates/type_map.hpp"

// Boolean operations for parameter pack
#include "templates/bool_operations.hpp"

#endif