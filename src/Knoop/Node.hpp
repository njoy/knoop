template< typename... Ts > using void_t = void;

template< typename... Ls >
class Node {
public:
  using ptr_type = std::shared_ptr< Node >;
  using leaf_type = std::variant< Ls... >;
  using array_type = std::vector< ptr_type >;
  using map_type = std::map< std::string, array_type >;

  using core_type = std::variant<
    leaf_type,
    array_type,
    map_type
  >;

protected:
  core_type core;

public:
  #include "Knoop/Node/src/ctor.hpp"

  static Node array(){
    return Node( array_type{} );
  }

  static Node map(){
    return Node( map_type{} );
  }

  template< typename T >
  T get(){
    auto& leaf = std::experimental::get< leaf_type >( core );
    return std::experimental::get<T>(leaf);
  }

  template< typename T >
  Node& push_back( T&& t ){
    auto& array = std::experimental::get< array_type >( core );
    array.push_back( std::make_shared< Node >( t ) );

    return *this;
  }

  template< typename T >
  Node& insert( std::string str, T&& t ){
    auto& map = std::experimental::get< map_type >( core );
    map[ str ].push_back( std::make_shared< Node >( t ) );

    return *this;
  }

  Node& operator[]( size_t index ){
    auto& array = std::experimental::get< array_type >( core );
    return *(array.at( index ));
  }

  auto operator[]( const std::string& str ){
    auto& map = std::experimental::get< map_type >( core );
    
    return map[ str ] | ranges::view::indirect;
  }

  auto keys() const {
    auto& map = std::experimental::get< map_type >( core );
    return map | ranges::view::keys;
  }

  auto list() {
    auto& list = std::experimental::get< array_type >( core );

    return list | ranges::view::indirect;
  }

  auto values() const {
    auto& map = std::experimental::get< map_type >( core );
    return map 
        | ranges::view::values
        | ranges::view::transform( ranges::view::indirect );
  }

  template< typename T >
  Node& operator=( T&& t ){
    *this = Node( t );
    return *this;
  }
  Node& operator=( Node&& ) = default;
  Node& operator=( Node& ) = default;
  Node& operator=( const Node& ) = default;
};
