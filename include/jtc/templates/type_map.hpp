// Joel's Template Collection (JTC) - https://github.com/JoelFilho/JTC
// type_map.hpp: 1-to-1 mapping template for types.

// Copyright Joel P. C. Filho 2019 - 2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef JTC_TEMPLATES_TYPE_MAP_HPP
#define JTC_TEMPLATES_TYPE_MAP_HPP

#include "conditional.hpp"
#include "is_same.hpp"
#include "result_type.hpp"

namespace jtc {

//-------------------------------------------------------------------------------------------------
// type_map and map_node's definition
//
// Usage example: See 'unsigned_map' definition in 'make_signed_unsigned.hpp'.
//-------------------------------------------------------------------------------------------------

/// A map node to indicate the mapping from Key to Type
template <typename Key, typename Type>
struct map_node {
  /// Type of Key
  using key_type = Key;
  /// Type Key maps to
  using type = Type;
};

/// The map of types. Each node in Nodes should be a map_node.
template <typename... Nodes>
struct type_map {
  constexpr static auto size = sizeof...(Nodes);
};

//-------------------------------------------------------------------------------------------------
// Query function
//
// A result_type<true, Type>, defined from the first map_node<Key, Type> found in the
//  left-to-right search, where is_same_v<Key, Query>() == true.
//  Otherwise, returns result_type<false, /*undefined*/>, i.e. has no 'type' member.
//
// For an example, see the implementation of make_signed and make_unsigned.
//-------------------------------------------------------------------------------------------------

// Forward declaration of implementation
namespace detail { template <typename Map, typename Query> struct map_search_impl; }

/// Get the result of the search for key Query
template <typename Map, typename Query>
struct map_get : detail::map_search_impl<Map, Query> {};

/// Returns Type if there's a map_node<Query, Type> in Map.
template <typename Map, typename Query>
using map_get_t = typename map_get<Map, Query>::type;

/// Helper function to determine whether the key
template <typename Map, typename Query>
inline constexpr bool map_has_key() {
  return map_get<Map, Query>::value;
}

//-------------------------------------------------------------------------------------------------
// Mapping Inversion
//
// Creates a new type_map from Map, where each node is inverted,
//   i.e. each map_node<Key, Type> becomes map_node<Type, Key>.
//
// For a practical example, see 'signed_map' definition in 'make_signed_unsigned.hpp'.
//-------------------------------------------------------------------------------------------------

/// Inverts a Map node and stores it in the member 'type'
template <typename Node>
struct invert_node;

/// invert_node implementation for map_node
template <typename Key, typename Type>
struct invert_node<map_node<Key, Type>> : make_type<map_node<Type, Key>> {};

/// Alias to get the map_node resulting from inversion of Node.
template <typename Node>
using invert_node_t = typename invert_node<Node>::type;

/// Inverts the Map, and stores the resulting map in the member 'type'.
template <typename Map>
struct map_invert;

/// Map inversion implementation: apply invert_node for each map node.
template <typename... Nodes>
struct map_invert<type_map<Nodes...>> : make_type<type_map<invert_node_t<Nodes>...>> {};

/// Alias helper to get the type_map from map_invert.
template <typename Map>
using map_invert_t = typename map_invert<Map>::type;

//-------------------------------------------------------------------------------------------------
// map_get implementation. O(N) left-to-right linear search.
//-------------------------------------------------------------------------------------------------

namespace detail {

// Default search recursion
template <typename Query, typename Node, typename... Nodes>
struct search_iter : conditional_t<is_same_v<Query, typename Node::key_type>(),  // Has the key been found?
                                   result_type<true, typename Node::type>,       // Yes: return the result.
                                   search_iter<Query, Nodes...>> {};             // No: continue searching.

// Recusion stop condition: Single node in the map. Returns a positive result if Query and Key are the same.
template <typename Query, typename Node>
struct search_iter<Query, Node> : result_type<is_same_v<Query, typename Node::key_type>(), typename Node::type> {};

// Implementation, specialized to only access type_map's.
template <typename... Nodes, typename Query>
struct map_search_impl<type_map<Nodes...>, Query> : search_iter<Query, Nodes...> {};

}  // namespace detail
}  // namespace jtc

//-------------------------------------------------------------------------------------------------
// Compile-time Tests
//-------------------------------------------------------------------------------------------------

#ifndef JTC_NO_TESTS

namespace jtc {
namespace tests {

// TODO

}  // namespace tests
}  // namespace jtc

#endif  // JTC_NO_TESTS

#endif