
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

  // This creates a list of Node_t, but the list initially has only one element
  mNode.insert( "child", Node_t{1} );
  
  // We can create a second 'child' node, but this time, we must 'put' it on 
  // the map because the list of Nodes with the name of "child" is already there
  // Note that the two children nodes can have different types
  mNode.put( "child", Node_t{3.14} );
}
