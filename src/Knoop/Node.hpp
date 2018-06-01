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
  #include "Knoop/Node/src/push_back.hpp"
  #include "Knoop/Node/src/keys.hpp"
  #include "Knoop/Node/src/values.hpp"
  #include "Knoop/Node/src/list.hpp"
  #include "Knoop/Node/src/insert.hpp"
  #include "Knoop/Node/src/equalityOperator.hpp"
  #include "Knoop/Node/src/bracketOperator.hpp"
  #include "Knoop/Node/src/get.hpp"

  // Factories
  static Node array(){
    return Node( array_type{} );
  }
  static Node map(){
    return Node( map_type{} );
  }
};
