#define CATCH_CONFIG_MAIN

#include <map>
#include <memory>

#include "catch.hpp"

#include "Knoop.hpp"

using namespace njoy::Knoop;

SCENARIO( "testing the Node class" ){
  GIVEN( "attributes" ){
    std::map< std::string, std::string > attributes{
      {"name", "Anakin"}, {"surname", "Skywalker" }, {"born", "41 BBY"} };
    WHEN( "constructing an empty Node" ){
      Node knot( std::move( attributes ) );

      THEN( "the attribute values can be retrieved" ){
        REQUIRE( "Anakin" == knot.attribute( "name" ) );
        REQUIRE( "Skywalker" == knot.attribute( "surname" ) );
        REQUIRE( "41 BBY" == knot.attribute( "born" ) );
      }
    }

    WHEN( "constructing a node with text" ){
      std::string body( 
        "Anakin became Darth Vader when seduced by the Dark Side" );
      Node ani( std::move( attributes ), body );
    } // text node
    
    WHEN( "constructing a node with a double" ){
      double body{42};
      Node dNode( std::move( attributes ), body );
    } // text node

    WHEN( "constructing a node with a vector of doubles" ){
      std::vector< double > body{1.1, 42.0, 84.0};
      Node vdNode( std::move( attributes ), body );
    } // text node

    GIVEN( "children nodes" ){
      Node son( {{"name", "Leia"}, 
                {"surname", "Skywalker" }, 
                {"born", "19 BBY"}} );
      Node daughter( {{"name", "Leia"}, 
                      {"surname", "Skywalker" }, 
                      {"born", "19 BBY"}} );
      std::multimap< std::string, std::unique_ptr< Node > > children;
      children.emplace( "child", std::make_unique< Node >( son ) );
      children.emplace( "child", std::make_unique< Node >( daughter ) );

      Node family(attributes, children);
    }
  } // GIVEN
  GIVEN( "no attributes" ){
    WHEN( "constructing an empty Node" ){
      Node knot;

      THEN( "we can ensure that there are no attributes" ){
        auto attributes = knot.attributes();
        REQUIRE( attributes.empty() );
        REQUIRE( attributes.end() == attributes.find( "name" ) );
      }
    }
  }
} // SCENARIO
