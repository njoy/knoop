class Node {
public:
  using core_type = std::variant<
    // std::multimap< std::string, std::unique_ptr< Node > >,
    std::vector< double >,
    std::string,
    double
  >;

protected:
  std::map< std::string, std::string > attributes_;
  core_type core;

public:
  #include "Knoop/Node/src/ctor.hpp"

  std::string 
  attribute( std::string name ){ return attributes_.find( name )->second; }
  auto& attributes( ){ return attributes_; }

};
