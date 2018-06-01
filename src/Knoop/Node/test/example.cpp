#include "catch.hpp"

#include "Knoop.hpp"

using namespace njoy::Knoop;

using Node_t = Node<int, double, std::string, std::vector< double > >;

struct Attribute : std::pair< std::string, std::string >{
  using std::pair< std::string, std::string >::pair;
};
struct Element : std::pair< std::string, Node_t >{
  using std::pair< std::string, Node_t >::pair;
};

Node_t GNDSNode(){
  auto mNode = Node_t::map();
  mNode.insert( "attributes", Node_t::map() );
  return mNode;
}

template< typename... Ts >
Node_t GNDSNode( Attribute attribute, 
                 Ts&& ... ts ){
  auto gndsNode = GNDSNode( std::forward< Ts >( ts ) ... );
  gndsNode["attributes"].front().insert(attribute.first, attribute.second);
  return gndsNode;
}


template< typename... Ts >
Node_t GNDSNode( Element element,
                 Ts&&... ts ){
  auto gndsNode = GNDSNode( std::forward< Ts >( ts ) ... );
  gndsNode.insert( element.first, element.second );

  return gndsNode;
}

SCENARIO( "Simulating GNDS" ){
  GIVEN( "a node" ){
    auto gndsNode = GNDSNode();
    REQUIRE( "attributes" == gndsNode.keys().front() );
  }

  GIVEN( "a node with some attributes and a 'child'" ){

    auto gndsNode = 
        GNDSNode( Attribute{ "name", "Anakin" }, 
                  Attribute{ "surname", "Skywalker"},
                  Element{ "child", GNDSNode( Attribute{ "name", "Luke" } ) } );

    THEN( "the attributes can be checked" ){
      auto attributes = gndsNode["attributes"].front();
      std::string value = attributes[ "name" ].front().get< std::string >();
      REQUIRE( "Anakin" == value );
      value = attributes[ "surname" ].front().get< std::string >();
      REQUIRE( "Skywalker" == value );
    }

    WHEN( "children are added" ){
      gndsNode.insert( "child", GNDSNode( Attribute{"name", "Leia" } ) );
    }
  }
} // SCENARIO

