// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// type_traits.hpp: Type properties for template programming

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TYPE_TRAITS_HPP
#define JTC_TYPE_TRAITS_HPP

//-------------------------------------------------------------------------------------------------
// Basic types
//-------------------------------------------------------------------------------------------------

// C++20's type_identity, aliased as make_type in this library
#include "templates/make_type.hpp"

// Emulates std::integral_constant and std::bool_constant
#include "templates/integral_constant.hpp"

// std::enable_if
#include "templates/enable_if.hpp"

// std::conditional
#include "templates/conditional.hpp"

// Emulates std::void_t and implements sfinae_t
#include "templates/sfinae_types.hpp"

//-------------------------------------------------------------------------------------------------
// Type comparators
//-------------------------------------------------------------------------------------------------

// std::is_same
#include "templates/is_same.hpp"

// are_same, an implementation for parameter packs
#include "templates/are_same.hpp"

//-------------------------------------------------------------------------------------------------
// Qualifier-based traits
//-------------------------------------------------------------------------------------------------

// std::[add/remove/is]_[const/volatile/reference/cv/cvref]
// Plus an implementation for copy_[const/volatile/reference/cv/cvref]
#include "templates/cv_ref_traits.hpp"

//-------------------------------------------------------------------------------------------------
// Numerical Traits
//-------------------------------------------------------------------------------------------------

// std::'s is_integral, is_floating_point, is_arithmetic, is_signed, is_unsigned...
#include "templates/number_traits.hpp"

// std::make_signed and std::make_unsigned
#include "templates/make_signed_unsigned.hpp"

#endif