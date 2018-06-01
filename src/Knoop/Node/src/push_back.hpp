template< typename T >
Node& push_back( T&& t ){
  auto& array = std::experimental::get< array_type >( core );
  array.push_back( std::make_shared< Node >( t ) );

  return *this;
}
