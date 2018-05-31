class Node {
  std::map< std::string, std::string > attributes_;

public:
  #include "Knoop/Node/src/ctor.hpp"

  std::string 
  attribute( std::string name ){ return attributes_.find( name )->second; }
  auto& attributes( ){ return attributes_; }

};
