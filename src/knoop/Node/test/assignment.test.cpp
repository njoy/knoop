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

SCENARIO( "assignment" ){
  GIVEN("two nodes"){
    THEN("nodes can assigned from other nodes"){
      auto iNode = Node_t{ 3 };
      auto sNode = Node_t{ "abc" };
      auto temp = iNode;
      iNode = sNode;
      sNode = temp;
      REQUIRE(getString(iNode) == "abc");
      REQUIRE(getInt(sNode) == 3);
    }

    THEN("nodes can assigned from values"){
      auto node = Node_t{"hello"};
      REQUIRE(getString(node) == "hello");
      node = 4;
      REQUIRE(getInt(node) == 4);
      node = "world";
      REQUIRE(getString(node) == "world");
    }
  }
}
