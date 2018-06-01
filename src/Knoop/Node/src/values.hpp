auto values() const {
  auto& map = std::experimental::get< map_type >( core );
  return map 
      | ranges::view::values
      | ranges::view::transform( ranges::view::indirect );
}
