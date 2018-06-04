template< typename T >
Node& put( std::string str, T&& t ){
  auto& map = std::experimental::get< map_type >( core );
  auto shared = std::make_shared< Node >( t );

  auto p = map.emplace( str, std::move( shared ) );

  if ( not p.second ){ 
    p.first->second = std::move( shared );
  }
  return *this;
}

