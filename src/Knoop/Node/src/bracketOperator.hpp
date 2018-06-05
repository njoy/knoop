Node& operator[]( const std::string& str ){
  auto& map = std::experimental::get< map_type >( core );
  
  return *( map[ str ] );
}
