
#include <iostream>
#include <vector>

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
  // This makes a Node for each value passed in
  Node_t varNode{1.1, 2, "three"};

  // We can get a list of each of the Nodes
  auto list = varNode.list();
  // and can iterate through it as we would from the STL
  auto it = list.begin();
  cout << endl;
  cout << "varNode has double value: " << (*it).get< double> () << endl;
  ++it;
  cout << "varNode has int value: " << (*it).get< int >() << endl;
  ++it;
  cout << "varNode has string value: " << (*it).get< std::string >() << endl;
  ++it;


  Node< std::vector< double > > vNode{
      std::vector< double >{1.0, 2.0, 3.0, 4.0} };
  auto& vec = vNode.get< std::vector< double > >();
  cout << endl;
  cout << "vNode has values: "
       << vec[0] << ", "
       << vec[1] << ", "
       << vec[2] << ", "
       << vec[3] << ", "
       << endl;

  // Example of how to create nested nodes
  nesting();
}
