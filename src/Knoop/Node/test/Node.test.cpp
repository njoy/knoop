#define CATCH_CONFIG_MAIN

#include <map>
#include <memory>
#include <iostream>

#include "catch.hpp"

#include "Knoop.hpp"

using namespace njoy::Knoop;

using Node_t = Node<int, double, std::string, std::vector< double > >;

SCENARIO( "testing the Node class" ){
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
  GIVEN( "an list Node" ){
    auto aNode = Node_t::makeList();

    WHEN( "values have been 'push_back'-ed" ){
      aNode.push_back(1.0).push_back(2).push_back(3.14).push_back(42);

      THEN( "the values can be verified" ){

        auto list = aNode.list();
        auto it = list.begin();
        REQUIRE( 1.0  == it->get< double >() ); ++it;
        REQUIRE( 2    == it->get< int >() ); ++it;
        REQUIRE( 3.14 == it->get< double >() ); ++it;
        REQUIRE( 42   == it->get< int >() ); ++it;

      }
    }
  } // GIVEN list Node
  GIVEN( "a map Node" ){
    auto mNode = Node_t::makeMap();

    WHEN( "values have been inserted" ){
      auto getString = []( const Node_t& ele ){ 
        return ele.get< std::string >(); 
      };

      mNode.insert( "name", "Anakin" );
      mNode.insert( "surname", "Skywalker" );

      REQUIRE( "Anakin" == getString( mNode[ "name" ] ) );
      REQUIRE( "Skywalker" == getString( mNode[ "surname" ] ) );

      REQUIRE_THROWS( mNode.insert( "name", "Darth" ) );

      mNode.put( "name", "Darth" ).put( "surname", "Vader" );
      REQUIRE( "Darth" == getString( mNode[ "name" ] ) );
      REQUIRE( "Vader" == getString( mNode[ "surname" ] ) );
      
    }
  } // GIVEN map
} // SCENARIO
