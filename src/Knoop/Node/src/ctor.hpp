Node( std::map< std::string, std::string >&& attributes ):
  attributes_( attributes )

{ }

Node( ):
  Node( std::map< std::string, std::string >() )
{ }
