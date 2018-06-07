#include "catch.hpp"
#include "knoop.hpp"

using namespace njoy::knoop;
using Node_t = Node<int, std::string>;

// this functions are a workaround for isuues in the interaction between
// C macros (like Catch's REQUIRE statement) and C++ template
// instatiations;

int& getInt(Node_t& node);
const int& getInt(const Node_t& node);
std::string& getString(Node_t& node);
const std::string& getString(const Node_t& node);

SCENARIO( "map" ){
  GIVEN( "a map Node" ){
    auto mNode = Node_t::makeMap();

    WHEN( "values can be inserted" ){
      mNode.insert( "name", "Anakin" )
           .insert( "surname", "Skywalker" )
           .insert( "age", 22 );

      REQUIRE(ranges::equal({"age", "name", "surname"}, mNode.keys()));

      auto it = mNode.values().begin();
      REQUIRE(22 == getInt(*it)); ++it;
      REQUIRE("Anakin" == getString(*it)); ++it;
      REQUIRE("Skywalker" == getString(*it)); ++it;

      REQUIRE( "Anakin" == getString( mNode[ "name" ] ) );
      REQUIRE( "Skywalker" == getString( mNode[ "surname" ] ) );
      REQUIRE( 22 == getInt( mNode[ "age" ] ) );

      THEN("inserting an existing node will throw"){
        REQUIRE_THROWS( mNode.insert( "name", "Darth" ) );
      }

      mNode.put( "name", "Darth" ).put( "surname", "Vader" );

      REQUIRE( "Darth" == getString( mNode[ "name" ] ) );
      REQUIRE( "Vader" == getString( mNode[ "surname" ] ) );

      REQUIRE( mNode.contains( "name" ) );
      mNode.erase( "name" );
      REQUIRE_THROWS( mNode[ "name" ] );
      REQUIRE( not mNode.contains( "name" ) );
    }
  }
}
