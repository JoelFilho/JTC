// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// cv_ref_traits.hpp: Removal and addition of qualifiers and references to types
//                    Defines the standard [is/add/remove] operations for references and qualifiers
//                    Introduces two new operations: add_*_if and copy_// to easily operate on these properties

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)


#ifndef JTC_TEMPLATES_CV_REF_TRAITS_HPP
#define JTC_TEMPLATES_CV_REF_TRAITS_HPP

#include "integral_constant.hpp"
#include "make_type.hpp"

namespace jtc {

//-------------------------------------------------------------------------------------------------
// Identification Traits
//
// Define whether the types match the specified properties.
//
// Usage examples:
//   static_assert(is_const<const int>::value, "Should be const");
//   static_assert(is_rvalue_reference<long long&&>::value, "Should be reference");
//
// Additionally, the _v() helpers are defined and equivalent to accessing ::value:
//   static_assert(is_const_v<const int>(), "Should be const");
//-------------------------------------------------------------------------------------------------

template <typename T> struct is_const          : false_type {};
template <typename T> struct is_const<const T> : true_type {};
template <typename T> inline constexpr bool is_const_v() { return is_const<T>::value; }

template <typename T> struct is_volatile             : false_type {};
template <typename T> struct is_volatile<volatile T> : true_type {};
template <typename T> inline constexpr bool is_volatile_v() { return is_volatile<T>::value; }

template <typename T> struct is_lvalue_reference     : false_type {};
template <typename T> struct is_lvalue_reference<T&> : true_type {};
template <typename T> inline constexpr bool is_lvalue_reference_v() { return is_lvalue_reference<T>::value; }

template <typename T> struct is_rvalue_reference      : false_type {};
template <typename T> struct is_rvalue_reference<T&&> : true_type {};
template <typename T> inline constexpr bool is_rvalue_reference_v() { return is_rvalue_reference<T>::value; }

//-------------------------------------------------------------------------------------------------
// Addition Traits
//
// Add the qualifiers and references to types.
//
// Additionally, the _t helpers are defined and equivalent to accessing ::type.
//
// For a practical example, see declval's declaration.
//-------------------------------------------------------------------------------------------------

// add_[lvalue/rvalue]_reference implementation
namespace detail {
template <typename T> auto add_rvalue_impl(int) -> make_type<T&&>;
template <typename T> auto add_rvalue_impl(...) -> make_type<T>;

template <typename T> auto add_lvalue_impl(int) -> make_type<T&>;
template <typename T> auto add_lvalue_impl(...) -> make_type<T>;
} // namespace detail

template <typename T> struct add_lvalue_reference : decltype(detail::add_lvalue_impl<T>(0)) {};
template <typename T> using  add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template <typename T> struct add_rvalue_reference : decltype(detail::add_rvalue_impl<T>(0)) {};
template <typename T> using  add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

template <typename T> struct add_const   : make_type<const T> {};
template <typename T> using  add_const_t = typename add_const<T>::type;

template <typename T> struct add_volatile   : make_type<volatile T> {};
template <typename T> using  add_volatile_t = typename add_volatile<T>::type;

template <typename T> struct add_cv   : make_type<const volatile T> {};
template <typename T> using  add_cv_t = typename add_cv<T>::type;

//-------------------------------------------------------------------------------------------------
// Removal Traits
//
// Remove qualifiers and references from types.
//
// Additionally, the _t helpers are defined and equivalent to accessing ::type.
//
// For an example, see the implementation of move and forward in move_forward.hpp
//-------------------------------------------------------------------------------------------------

template <typename T> struct remove_reference      : make_type<T> {};
template <typename T> struct remove_reference<T&>  : make_type<T> {};
template <typename T> struct remove_reference<T&&> : make_type<T> {};
template <typename T> using  remove_reference_t    = typename remove_reference<T>::type;

template <typename T> struct remove_const          : make_type<T> {};
template <typename T> struct remove_const<const T> : make_type<T> {};
template <typename T> using  remove_const_t        = typename remove_const<T>::type;

template <typename T> struct remove_volatile             : make_type<T> {};
template <typename T> struct remove_volatile<volatile T> : make_type<T> {};
template <typename T> using  remove_volatile_t           = typename remove_volatile<T>::type;

template <typename T> struct remove_cv   : make_type<remove_const_t<remove_volatile_t<T>>> {};
template <typename T> using  remove_cv_t = typename remove_cv<T>::type;

template <typename T> struct remove_cvref   : make_type<remove_cv_t<remove_reference_t<T>>> {};
template <typename T> using  remove_cvref_t = typename remove_cvref<T>::type;

//-------------------------------------------------------------------------------------------------
// Conditional Addition
//
// Add qualifiers and references to a type T if the boolean parameter B evaluates to true.
//
// Additionally, the _t helpers are defined and equivalent to accessing ::type.
//-------------------------------------------------------------------------------------------------

template <bool B, typename T> struct add_lvalue_reference_if          : make_type<T> {};
template <typename T>         struct add_lvalue_reference_if<true, T> : make_type<add_lvalue_reference_t<T>> {};
template <bool B, typename T> using  add_lvalue_reference_if_t        = typename add_lvalue_reference_if<B, T>::type;

template <bool B, typename T> struct add_rvalue_reference_if          : make_type<T> {};
template <typename T>         struct add_rvalue_reference_if<true, T> : make_type<add_rvalue_reference_t<T>> {};
template <bool B, typename T> using  add_rvalue_reference_if_t        = typename add_rvalue_reference_if<B, T>::type;

template <bool B, typename T> struct add_const_if          : make_type<T> {};
template <typename T>         struct add_const_if<true, T> : make_type<const T> {};
template <bool B, typename T> using  add_const_if_t        = typename add_const_if<B, T>::type;

template <bool B, typename T> struct add_volatile_if          : make_type<T> {};
template <typename T>         struct add_volatile_if<true, T> : make_type<volatile T> {};
template <bool B, typename T> using  add_volatile_if_t        = typename add_volatile_if<B, T>::type;

template <bool B, typename T> struct add_cv_if          : make_type<T> {};
template <typename T>         struct add_cv_if<true, T> : make_type<const volatile T> {};
template <bool B, typename T> using  add_cv_if_t        = typename add_cv_if<B, T>::type;

//-------------------------------------------------------------------------------------------------
// Qualifier and reference replication
//
// Add qualifiers and references to a type To if the type
//
// Additionally, the _t helpers are defined and equivalent to accessing ::type.
//
// For an usage example, see make_signed and make_unsigned's implementation.
//-------------------------------------------------------------------------------------------------

template <typename From, typename To> struct copy_reference             : make_type<To> {};
template <typename From, typename To> struct copy_reference<From&, To>  : make_type<add_lvalue_reference_t<To>> {};
template <typename From, typename To> struct copy_reference<From&&, To> : make_type<add_rvalue_reference_t<To>> {};
template <typename From, typename To> using  copy_reference_t           = typename copy_reference<From, To>::type;

template <typename From, typename To> struct copy_const                 : make_type<To> {};
template <typename From, typename To> struct copy_const<const From, To> : make_type<const To> {};
template <typename From, typename To> using  copy_const_t               = typename copy_const<From, To>::type;

template <typename From, typename To> struct copy_volatile                    : make_type<To> {};
template <typename From, typename To> struct copy_volatile<volatile From, To> : make_type<volatile To> {};
template <typename From, typename To> using  copy_volatile_t                  = typename copy_volatile<From, To>::type;

template <typename From, typename To> struct copy_cv   : make_type<copy_const_t<From, copy_volatile_t<From, To>>> {};
template <typename From, typename To> using  copy_cv_t = typename copy_cv<From, To>::type;

template <typename From, typename To> struct copy_cvref   : make_type<copy_cv_t<From, copy_reference_t<From, To>>> {};
template <typename From, typename To> using  copy_cvref_t = typename copy_cvref<From, To>::type;

} // namespace jtc

//-------------------------------------------------------------------------------------------------
// Compile-time Tests
//-------------------------------------------------------------------------------------------------

#ifndef JTC_NO_TESTS

namespace jtc {
namespace tests {

// TODO
// Bless my poor soul

} // namespace tests
} // namespace jtc

#endif // JTC_NO_TESTS

#endif