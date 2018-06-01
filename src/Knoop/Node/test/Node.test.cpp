#define CATCH_CONFIG_MAIN

#include <map>
#include <memory>

#include "catch.hpp"

#include "Knoop.hpp"

using namespace njoy::Knoop;

SCENARIO( "testing the Node class" ){
  using Node_t = Node<int, double, std::string, std::vector< double > >;
  GIVEN( "an instance of a leaf type" ){
    auto iNode = Node_t{ 3 };
    auto dNode = Node_t{ 3.14 };
    std::vector< double > refVec{5, 6, 7, 8 };
    auto vNode = Node_t{ refVec };
    auto sNode = Node_t{ "abc" };

    THEN( "the leaf value can be extracted" ){
      REQUIRE( 3 == iNode.get< int >() );
      REQUIRE( 3.14 == dNode.get< double >() );
      REQUIRE( refVec == vNode.get< std::vector< double > >() );
      REQUIRE( "abc" == sNode.get< std::string >() );

      AND_THEN( "an exception is thrown when asking for the wrong type" ){
        REQUIRE_THROWS( iNode.get< double >() );
        REQUIRE_THROWS( dNode.get< int >() );
        REQUIRE_THROWS( vNode.get< int >() );
        REQUIRE_THROWS( sNode.get< int >() );
      }
    }
    THEN( "the value can be changed" ){
      iNode = 1.0;
      dNode = 10;
      AND_THEN( "the new values can be assured" ){
        REQUIRE( 1.0 == iNode.get< double >() );
        REQUIRE( 10 == dNode.get< int >() );
      }
    }
  } // GIVEN leaf type
  GIVEN( "an array Node" ){
    auto aNode = Node_t::array();

    WHEN( "values have been 'push_back'-ed" ){
      aNode.push_back(1.0).push_back(2).push_back(3.14).push_back(42);

      THEN( "the values can be verified" ){
        REQUIRE( 1.0  == aNode[ 0 ].get< double >() );
        REQUIRE( 2    == aNode[ 1 ].get< int >() );
        REQUIRE( 3.14 == aNode[ 2 ].get< double >() );
        REQUIRE( 42   == aNode[ 3 ].get< int >() );

        auto list = aNode.list();
        REQUIRE( 1.0  == list[ 0 ].get< double >() );
        REQUIRE( 2    == list[ 1 ].get< int >() );
        REQUIRE( 3.14 == list[ 2 ].get< double >() );
        REQUIRE( 42   == list[ 3 ].get< int >() );

        AND_THEN( "array overbounds throws an exception" ){
          REQUIRE_THROWS( aNode[ 4 ] );
        }
      }
    }
  } // GIVEN array Node
  GIVEN( "a map Node" ){
    auto mNode = Node_t::map();

    WHEN( "values have been inserted" ){
      auto getString = []( Node_t& ele ){ return ele.get< std::string >(); };

      mNode.insert( "name", "Anakin" ).insert( "surname", "Skywalker" );
      mNode.insert( "name", "Darth" ).insert( "surname", "Vader" );
      
      THEN( "the values can be verified" ){

        REQUIRE( ranges::equal( {"Anakin", "Darth"}, 
            mNode[ "name" ] | ranges::view::transform(  getString ) ) );
        REQUIRE( ranges::equal( {"Skywalker", "Vader"}, 
            mNode[ "surname" ] | ranges::view::transform(  getString ) ) );
      }

      THEN( "the keys and values can be extracted" ){
        auto keys = mNode.keys();
        auto values = mNode.values().front();
        REQUIRE( ranges::equal( { "name", "surname" }, keys ) );
        REQUIRE( ranges::equal( { "Anakin", "Darth" }, 
                 values | ranges::view::transform( getString ) ) );
      }
    }
  }
} // SCENARIO
