template<typename String>
const Node& operator[]( String&& str ) const {
  const auto& map = std::get< map_type >( core );
  return *( map.at( str ) );
}


template<typename String>
Node& operator[]( String&& str ){
  auto& map = std::get< map_type >( core );
  return *( map.at( str ) );
}
