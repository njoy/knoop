#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "knoop.hpp"
using Node_t = njoy::knoop::Node<int, std::string>;

int& getInt(Node_t& node){
  return node.template get<int>();
}

const int& getInt(const Node_t& node){
  return node.template get<int>();
}

std::string& getString(Node_t& node){
  return node.template get<std::string>();
}

const std::string& getString(const Node_t& node){
  return node.template get<std::string>();
}
