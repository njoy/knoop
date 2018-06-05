template< typename T >
Node& push_back( T&& t ){
  auto& list = std::experimental::get< list_type >( core );
   list.emplace_back( t );

  return *this;
}