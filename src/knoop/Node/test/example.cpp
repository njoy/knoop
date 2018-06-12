#include <iostream>

#include "catch.hpp"

#include "knoop.hpp"

using namespace njoy::knoop;

using Node_t = Node<int, double, std::string, std::vector< double > >;

template< typename... Ts >
Node_t GNDSNode( const std::string&, Node_t, Ts&&... );

struct Attribute : std::pair< std::string, std::string >{
  using std::pair< std::string, std::string >::pair;
};

Node_t GNDSNode( const std::string& name ){
  auto mNode = Node_t::makeMap();

  mNode.insert( "name", name );
  mNode.insert( "attributes", Node_t::makeMap() );
  mNode.insert( "children", Node_t::makeList() );
  return mNode;
}

template< typename... Ts >
Node_t GNDSNode( const std::string& name, Attribute attribute, Ts&& ... ts ){

  auto gndsNode = GNDSNode( name, std::forward< Ts >( ts ) ... );
  gndsNode["attributes"].insert(attribute.first, attribute.second);
  return gndsNode;
}


template< typename... Ts >
Node_t GNDSNode( const std::string& name, Node_t element, Ts&&... ts ){
  auto gndsNode = GNDSNode( name,  std::forward< Ts >( ts ) ... );
  gndsNode[ "children" ].push_front( element );

  return gndsNode;
}

SCENARIO( "Simulating GNDS" ){
  GIVEN( "a node" ){
    auto gndsNode = GNDSNode( "person" );
    REQUIRE( "attributes" == gndsNode.keys().front() );
  }

  GIVEN( "a node with some attributes and a 'child'" ){

    auto gndsNode = 
        GNDSNode( "person",
          Attribute{ "name", "Anakin" }, 
          Attribute{ "surname", "Skywalker"},
          GNDSNode( "person", 
                    Attribute{ "name", "Luke" },
                    Attribute{ "surname", "Skywalker" } ),
          GNDSNode( "person", 
                   Attribute{ "name", "Obi-Wan" },
                   Attribute{ "surname", "Kenobi" } ) );

    THEN( "the attributes can be checked" ){
      auto attributes = gndsNode["attributes"];

      std::string value = attributes[ "name" ].get< std::string >();
      REQUIRE( "Anakin" == value );
      value = attributes[ "surname" ].get< std::string >();
      REQUIRE( "Skywalker" == value );

      REQUIRE( 2 == gndsNode[ "children" ].list().size() );
    }

    auto isSkywalker = []( const Node_t& node ){ 
      auto surname = node[ "attributes" ][ "surname" ]. get< std::string>();
      return surname == "Skywalker";
    };
    THEN( "we can find all the Skywalkers" ){
      auto children = gndsNode[ "children" ].list()
          | ranges::view::filter( isSkywalker );

      REQUIRE( 1 == ranges::distance( children.begin(), children.end() ) );
      REQUIRE( isSkywalker( children.front() ) );

      WHEN( "children are added" ){
        gndsNode[ "children" ].push_back( 
          GNDSNode( "person", 
                    Attribute{"name", "Leia" },
                    Attribute{ "surname", "Skywalker" } ) );

        REQUIRE( 3 == gndsNode[ "children" ].list().size() );
        auto children = gndsNode[ "children" ].list()
            | ranges::view::filter( isSkywalker );
        REQUIRE( 2 == ranges::distance( children.begin(), children.end() ) );
      }
    }

  }
} // SCENARIO

