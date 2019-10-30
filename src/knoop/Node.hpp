template< typename... Ts >
using void_t = void;

template< typename... Ls >
class Node {
public:
  using leaf_type = std::variant< Ls... >;
  using list_type = std::list< Node >;
  using list_iterator = typename list_type::iterator;
  using ptr_type = valuable::value_ptr< Node >;
  using map_type = std::map< std::string, ptr_type, std::less<> >;
  using core_type = std::variant< leaf_type, list_type, map_type >;

protected:
  core_type core;

public:
  #include "knoop/Node/src/ctor.hpp"
  #include "knoop/Node/src/assignmentOperator.hpp"

  #include "knoop/Node/src/list.hpp"
  #include "knoop/Node/src/push_back.hpp"
  #include "knoop/Node/src/push_front.hpp"
  #include "knoop/Node/src/pop_back.hpp"
  #include "knoop/Node/src/pop_front.hpp"
  #include "knoop/Node/src/front.hpp"
  #include "knoop/Node/src/back.hpp"

  #include "knoop/Node/src/keys.hpp"
  #include "knoop/Node/src/values.hpp"
  #include "knoop/Node/src/put.hpp"
  #include "knoop/Node/src/contains.hpp"
  #include "knoop/Node/src/bracketOperator.hpp"

  #include "knoop/Node/src/insert.hpp"
  #include "knoop/Node/src/erase.hpp"
  #include "knoop/Node/src/get.hpp"

  // Factories
  static Node makeList(){
    return { list_type{} };
  }
  static Node makeMap(){
    return { map_type{} };
  }
};
