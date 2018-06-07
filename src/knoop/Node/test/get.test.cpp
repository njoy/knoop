#include "knoop.hpp"
#include "catch.hpp"

using namespace njoy::knoop;
using Node_t = Node<int, std::string>;

// this functions are a workaround for isuues in the interaction between
// C macros (like Catch's REQUIRE statement) and C++ template
// instatiations;

int& getInt(Node_t& node);
const int& getInt(const Node_t& node);

SCENARIO( "leaf node value extraction" ){
  SECTION("the get function returns a reference"){
    auto iNode = Node_t{ 3 };
    const auto& ciNode = iNode;

    int& integer = getInt(iNode);
    REQUIRE(integer == 3);

    // Doesn't compile!
    //
    // int& invalid = ciNode.get<int>();
    //
    // Const nodes return a constant reference, which cannot be used
    // to initialize a mutable reference.

    const int& cinteger = getInt(ciNode);
    REQUIRE(cinteger == 3);
  }

  SECTION("requiring the wrong type throws an exception"){
    auto sNode = Node_t{"hello world"};
    const auto& csNode = sNode;

    REQUIRE_THROWS(getInt(sNode));
    REQUIRE_THROWS(getInt(csNode));
  }
}
