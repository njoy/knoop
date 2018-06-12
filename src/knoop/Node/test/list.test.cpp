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

SCENARIO( "list" ){
  GIVEN( "a list Node" ){
    WHEN( "values can be 'push_back'-ed" ){
      auto aNode = Node_t::makeList();
      aNode.push_back(1).push_back("hello");
      aNode.push_back("world", 2, 3);

      auto it = aNode.list().begin();
      REQUIRE(1 == getInt(*it)); ++it;
      REQUIRE("hello" == getString(*it)); ++it;
      REQUIRE("world" == getString(*it)); ++it;
      REQUIRE(2 == getInt(*it)); ++it;
      REQUIRE(3 == getInt(*it)); ++it;
      REQUIRE(aNode.list().end() == it);

      THEN("the list could be 'pop_back'-ed"){
        auto it = aNode.list().begin();
        aNode.pop_back().pop_back().pop_back();
        REQUIRE(1 == getInt(*it)); ++it;
        REQUIRE("hello" == getString(*it)); ++it;
        REQUIRE(aNode.list().end() == it);
      }
    }

    WHEN( "values can be 'push_front'-ed" ){
      auto aNode = Node_t::makeList();
      aNode.push_front(1).push_front("hello");
      aNode.push_front("world", 2, 3);

      auto it = std::make_reverse_iterator(aNode.list().end());
      auto end = std::make_reverse_iterator(aNode.list().begin());
      REQUIRE(1 == getInt(*it)); ++it;
      REQUIRE("hello" == getString(*it)); ++it;
      REQUIRE(3 == getInt(*it)); ++it;
      REQUIRE(2 == getInt(*it)); ++it;
      REQUIRE("world" == getString(*it)); ++it;

      REQUIRE(end == it);

      THEN("the list could be 'pop_front'-ed"){
        aNode.pop_front().pop_front().pop_front();
        auto it = std::make_reverse_iterator(aNode.list().end());
        auto end = std::make_reverse_iterator(aNode.list().begin());
        REQUIRE(1 == getInt(*it)); ++it;
        REQUIRE("hello" == getString(*it)); ++it;
        REQUIRE(end == it);
      }
    }

    WHEN( "values can be inserted" ){
      auto aNode = Node_t::makeList();
      // insert at the end
      auto end = aNode.list().end();
      aNode.insert(end, 1).insert(end, 2).insert(end, "abc");
      // insert at the beginning
      auto it = aNode.list().begin();
      aNode.insert(it, 3, 4, "def");
      // insert at the middle
      aNode.insert(it, 5, 6, "ghi");

      it = aNode.list().begin();
      REQUIRE(3 == getInt(*it)); ++it;
      REQUIRE(4 == getInt(*it)); ++it;
      REQUIRE("def" == getString(*it)); ++it;
      REQUIRE(5 == getInt(*it)); ++it;
      REQUIRE(6 == getInt(*it)); ++it;
      REQUIRE("ghi" == getString(*it)); ++it;
      REQUIRE(1 == getInt(*it)); ++it;
      REQUIRE(2 == getInt(*it)); ++it;
      REQUIRE("abc" == getString(*it)); ++it;
      REQUIRE(aNode.list().end() == it);

      THEN( "values can be erased" ){
        // erase at the end
        auto last = --(aNode.list().end());
        aNode.erase(last);
        // erase at the beginning
        aNode.erase(aNode.list().begin());
        // erase at the middle
        aNode.erase(std::next(aNode.list().begin(), 3));

        {
          auto it = aNode.list().begin();
          REQUIRE(4 == getInt(*it)); ++it;
          REQUIRE("def" == getString(*it)); ++it;
          REQUIRE(5 == getInt(*it)); ++it;
          REQUIRE("ghi" == getString(*it)); ++it;
          REQUIRE(1 == getInt(*it)); ++it;
          REQUIRE(2 == getInt(*it)); ++it;
          REQUIRE(aNode.list().end() == it);
        } {
          auto left = std::next(aNode.list().begin());
          auto right = std::next(left, 4);
          aNode.erase(left, right);
          auto it = aNode.list().begin();
          REQUIRE(4 == getInt(*it)); ++it;
          REQUIRE(2 == getInt(*it)); ++it;
          REQUIRE(aNode.list().end() == it);
        }
      }
    }
  }
  GIVEN( "values to build a list Node" ){
    Node_t list{ 1, 2, "hello", 4, 5 };
    auto listsList = list.list();
    REQUIRE( 1 == getInt( listsList.front() ) );
    REQUIRE( 5 == getInt( listsList.back() ) );

    auto it = listsList.begin();
    REQUIRE( 1 == getInt(*it) ); ++it;
    REQUIRE( 2 == getInt(*it) ); ++it;
    REQUIRE_THROWS( getInt(*it) );
    REQUIRE( "hello" == getString(*it) ); ++it;
    REQUIRE( 4 == getInt(*it) ); ++it;
    REQUIRE( 5 == getInt(*it) ); ++it;
    REQUIRE( it == listsList.end() );

  }
}
