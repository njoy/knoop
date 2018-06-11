
#include <iostream>
#include "knoop.hpp"

using namespace njoy::knoop;
using std::cout;
using std::endl;

void nesting();

int main( ){
  // We can create a node that takes only a single type
  Node<double> dNode{1.1};
  Node<int> iNode{2};
  Node< std::string > sNode{ "three" };

  // The leaf values of those nodes can be extracted and printed
  cout << "dNode has value: " << dNode.get< double >() << endl;
  cout << "iNode has value: " << iNode.get< int >() << endl;
  cout << "sNode has value: " << sNode.get< std::string >() << endl;

  // We can create a Node type that can take a variety of different leaf types
  using Node_t = Node< double, int, std::string >;
  Node_t varNode{1.1, 2, "three"};
  // cout << "varNode has double value: " << varNode.get< double >() << endl;
  // cout << "varNode has int value: " << varNode.get< int >() << endl;
  // cout << "varNode has string value: " << varNode.get< std::string >() << endl;

  // Example of how to create nested nodes
  nesting();

  return 0;
}
