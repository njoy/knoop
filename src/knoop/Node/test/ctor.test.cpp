#include "knoop.hpp"
#include "catch.hpp"

using namespace njoy::knoop;
using Node_t = Node<int, std::string>;

SCENARIO( "construction" ){
  SECTION("initialization from leaf type"){
    Node_t iNode{ 3 };
    Node_t sNode{ "abc" };

    SECTION("initialization from lvalue reference"){
      Node_t copy{ iNode };
    }

    SECTION("initialization from rvalue reference"){
      Node_t moved{ std::move(iNode) };
    }

    SECTION("initialization from argument list"){
      Node_t list{ 1, 2, "hello", iNode, 4, 5, std::move(sNode) };
    }
  }
}
