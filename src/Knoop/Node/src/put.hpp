template< typename T >
Node& put( std::string str, T&& t ){
  auto& map = std::experimental::get< map_type >( core );
  // auto shared = std::make_shared< Node >( t );

  auto p = map.emplace( str, t );

  if ( not p.second ){ 
    p.first->second = valuable::value_ptr< Node >{ std::move( t ) };
  }
  return *this;
}
