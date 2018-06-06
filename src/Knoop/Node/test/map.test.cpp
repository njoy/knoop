#include "catch.hpp"
#include "Knoop.hpp"

using namespace njoy::Knoop;
using Node_t = Node<int, std::string>;

SCENARIO( "map" ){
  // this lambda is a workaround for isuues in the interaction between
  // C macros (like Catch's REQUIRE statement) and C++ template
  // instatiations;
  auto getInt =
    [](auto&& node)
    // auto&& respects and preserves const-ness
    -> decltype(auto)
    // decltype(auto) explicit return type preserves reference-ness
    { return node.template get<int>(); };

  auto getString =
    [](auto&& node) -> decltype(auto)
    { return node.template get<std::string>(); };

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
