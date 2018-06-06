template< typename... Ts >
using void_t = void;

template< typename... Ls >
class Node {
public:
  using leaf_type = std::experimental::variant< Ls... >;
  using list_type = std::list< Node >;
  using list_iterator = typename list_type::iterator;
  using ptr_type = valuable::value_ptr< Node >;
  using map_type = std::map< std::string, ptr_type, std::less<> >;

  using core_type =
    std::experimental::variant< leaf_type, list_type, map_type >;

protected:
  core_type core;

public:
  #include "Knoop/Node/src/ctor.hpp"
  #include "Knoop/Node/src/assignmentOperator.hpp"

  #include "Knoop/Node/src/list.hpp"
  #include "Knoop/Node/src/push_back.hpp"
  #include "Knoop/Node/src/push_front.hpp"
  #include "Knoop/Node/src/pop_back.hpp"
  #include "Knoop/Node/src/pop_front.hpp"

  #include "Knoop/Node/src/keys.hpp"
  #include "Knoop/Node/src/values.hpp"
  #include "Knoop/Node/src/put.hpp"
  #include "Knoop/Node/src/contains.hpp"
  #include "Knoop/Node/src/bracketOperator.hpp"

  #include "Knoop/Node/src/insert.hpp"
  #include "Knoop/Node/src/erase.hpp"
  #include "Knoop/Node/src/get.hpp"

  // Factories
  static Node makeList(){
    return { list_type{} };
  }
  static Node makeMap(){
    return { map_type{} };
  }
};
