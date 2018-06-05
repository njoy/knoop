template< typename... Ts > using void_t = void;

template< typename... Ls >
class Node {
public:
  using ptr_type = valuable::value_ptr< Node >;
  using leaf_type = std::variant< Ls... >;
  using list_type = std::list< Node >;
  using map_type = std::map< std::string, ptr_type >;

  using core_type = std::variant<
    leaf_type,
    list_type,
    map_type
  >;

protected:
  core_type core;

public:
  #include "Knoop/Node/src/ctor.hpp"
  #include "Knoop/Node/src/push_back.hpp"
  #include "Knoop/Node/src/push_front.hpp"
  #include "Knoop/Node/src/keys.hpp"
  #include "Knoop/Node/src/values.hpp"
  #include "Knoop/Node/src/list.hpp"
  #include "Knoop/Node/src/insert.hpp"
  #include "Knoop/Node/src/equalityOperator.hpp"
  #include "Knoop/Node/src/bracketOperator.hpp"
  #include "Knoop/Node/src/get.hpp"
  #include "Knoop/Node/src/put.hpp"

  // Factories
  static Node makeList(){
    return Node( list_type{} );
  }
  static Node makeMap(){
    return Node( map_type{} );
  }
};
