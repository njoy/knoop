#include <iostream>

#include "catch.hpp"

#include "Knoop.hpp"

using namespace njoy::Knoop;

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
  mNode.insert( "elements", Node_t::makeList() );
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
  gndsNode[ "elements" ].push_front( element );

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

    // THEN( "the attributes can be checked" ){
      auto attributes = gndsNode["attributes"];

      std::string value = attributes[ "name" ].get< std::string >();
      REQUIRE( "Anakin" == value );
      value = attributes[ "surname" ].get< std::string >();
      REQUIRE( "Skywalker" == value );

      REQUIRE( 2 == gndsNode[ "elements" ].list().size() );
    // }

    // THEN( "we can find all the Skywalkers" ){
      auto isSkywalker = []( auto&& node ){ 
        auto name = node[ "attributes" ][ "surname" ].template 
            get< std::string>();
        std::cout << name << std::endl;
        return name == "Skywalker";
      };
      auto children = gndsNode[ "elements" ].list()
          | ranges::view::filter( isSkywalker );

      REQUIRE( 1 == ranges::distance( children.begin(), children.end() ) );
      REQUIRE( isSkywalker( children.front() ) );
      REQUIRE( not isSkywalker( children.back() ) );
      std::cout << std::endl;

      // WHEN( "children are added" ){
        gndsNode[ "elements" ].push_back( 
          GNDSNode( "person", 
                    Attribute{"name", "Leia" },
                    Attribute{ "surname", "Skywalker" } ) );

        REQUIRE( 3 == gndsNode[ "elements" ].list().size() );
        children = gndsNode[ "elements" ].list()
            | ranges::view::filter( isSkywalker );
        REQUIRE( 2 == ranges::distance( children.begin(), children.end() ) );
      // }
    // }

  }
} // SCENARIO

