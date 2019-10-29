Node& erase( list_iterator it ){
  auto& list = std::get< list_type >( core );
  list.erase( it );
  return *this;
}

Node& erase( list_iterator begin, list_iterator end ){
  auto& list = std::get< list_type >( core );
  list.erase( begin, end );
  return *this;
}

template< typename Str,
          typename = void_t< decltype( std::declval< map_type >()
                                       .at( std::declval< Str >() ) ) > >
Node& erase( Str&& str ){
  auto& map = std::get< map_type >( core );
  map.erase( str );
  return *this;
}
