Node( std::map< std::string, std::string >&& attributes,
       Node::core_type core = "" ):
  attributes_( attributes ),
  core( core )
{ }

Node( Node::core_type core ="" ):
  Node( std::map< std::string, std::string >(), core )
{ }
