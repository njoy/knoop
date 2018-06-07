template< typename Str >
bool contains( Str&& str ) const {
  const auto& map = std::experimental::get< map_type >( core );
  return map.count( str );
}
