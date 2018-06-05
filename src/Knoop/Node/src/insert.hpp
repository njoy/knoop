template< typename T >
Node& insert( std::string str, T&& t ){
  auto& map = std::experimental::get< map_type >( core );
  auto p = map.emplace( str, std::move( t ) );
  if ( not p.second ){ throw std::runtime_error("didn't work"); }
  return *this;
}
