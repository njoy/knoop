Node& operator[]( size_t index ){
  auto& array = std::experimental::get< array_type >( core );
  return *(array.at( index ));
}

auto operator[]( const std::string& str ){
  auto& map = std::experimental::get< map_type >( core );
  
  return map[ str ] | ranges::view::indirect;
}
