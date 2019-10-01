
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
  mNode.insert( "double", Node_t{ 1.1 } );
  mNode.insert( "int", Node_t{ 2 } ).insert( "string", Node_t{ "three" } );

  // We can replace (or insert) a child node by using 'put'
  mNode.put( "double", Node_t{3.14} );

  // This creates a child (sub) Node with an empty list
  mNode.put( "child", Node_t::makeList() );
  
  // This creates a child Node with a list that has been populated with the 
  // values you provided in the constructor
  mNode.put( "child", Node_t{ 4, 5.5, "six" } );

  // This will reassigns the node that is called 'child'
  mNode[ "child" ] = "seventy-five";

  // This causes a runtime exception because the "APM" child node does not (yet)
  // exist
  try {
    mNode[ "APM" ] = "crazy";
  } catch( std::exception& e ){
    cout << "You should not try to assign to a child that doesn't exist.";
  }
}
