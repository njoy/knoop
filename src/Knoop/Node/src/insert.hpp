template< typename T >
Node& insert( std::string str, T&& t ){
  auto& map = std::experimental::get< map_type >( core );
  map[ str ].push_back( std::make_shared< Node >( t ) );

  return *this;
}
