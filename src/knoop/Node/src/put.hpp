template< typename Str, typename T >
Node& put( Str&& str, T&& t ){
  auto& map = std::experimental::get< map_type >( core );
  auto it = map.find( str );
  if ( it != map.end() ){
    it->second = valuable::value_ptr< Node >{ std::forward<T>(t) };
  } else {
    map.emplace(str, std::forward<T>(t));
  }
  return *this;
}
