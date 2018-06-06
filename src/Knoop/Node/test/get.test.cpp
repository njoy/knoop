#include "Knoop.hpp"
#include "catch.hpp"

using namespace njoy::Knoop;
using Node_t = Node<int, std::string>;

SCENARIO( "leaf node value extraction" ){
  // this lambda is a workaround for isuues in the interaction between
  // C macros (like Catch's REQUIRE statement) and C++ template
  // instatiations;
  auto getInt =
    [](auto&& node)
    // auto&& respects and preserves const-ness
    -> decltype(auto)
    // decltype(auto) explicit return type preserves reference-ness
    { return node.template get<int>(); };

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
