template< typename Str, typename T,
          typename = void_t< decltype( std::declval< map_type >()
                                       .at( std::declval< Str >() ) ) > >
Node& insert( Str&& str, T&& t ){
  auto& map = std::get< map_type >( core );
  const auto p = map.emplace( str, std::forward<T>(t) );
  if ( not p.second ){ 
    throw std::runtime_error( "Error when inserting node"); 
  }
  return *this;
}

template< typename T >
Node& insert( const list_iterator it, T&& t ){
  auto& list = std::get< list_type >( core );
  list.insert(it, std::forward<T>(t) );
  return *this;
}

template< typename T, typename... Args >
Node& insert( const list_iterator it, T&& t, Args&&... args ){
  auto& list = std::get< list_type >( core );
  list.insert(it, std::forward<T>(t) );
  return this->insert(it, std::forward<Args>(args)... );
}
