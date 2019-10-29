auto keys() const {
  const auto& map = std::get< map_type >( core );
  return map | ranges::view::keys;
}
