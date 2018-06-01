auto keys() const {
  auto& map = std::experimental::get< map_type >( core );
  return map | ranges::view::keys;
}
