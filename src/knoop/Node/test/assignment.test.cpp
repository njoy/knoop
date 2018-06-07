#include "catch.hpp"
#include "knoop.hpp"

using namespace njoy::knoop;
using Node_t = Node<int, std::string>;

SCENARIO( "assignment" ){
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
