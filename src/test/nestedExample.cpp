
#include <iostream>

#include "knoop.hpp"

using namespace njoy::knoop;
using std::cout;
using std::endl;

void nesting(){

  cout << "\nNesting example" << endl;

  using Node_t = Node< double, int, std::string >;

  // Create a "map" type of node
  auto mNode = Node_t::makeMap();

  // Add some child nodes
  mNode.insert( "double", 1.1 );
  mNode.insert( "int", 2 ).insert( "string", "three" );

  mNode.insert( "child", Node_t::makeMap() );
  // auto child = mNode.get< std::map >();
  
  auto childNode = Node_t::makeMap();
  // mNode.insert( "child", std::move( cmNode ) );
}
