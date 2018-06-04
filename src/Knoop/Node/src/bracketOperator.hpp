Node& operator[]( size_t index ){
  auto& list = std::experimental::get< list_type >( core );
  return list.at( index );
}

Node& operator[]( const std::string& str ){
  auto& map = std::experimental::get< map_type >( core );
  
  return *( map[ str ] );
}
