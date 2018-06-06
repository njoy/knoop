auto values() const {
  const auto& map = std::experimental::get< map_type >( core );
  return map
      | ranges::view::values
      | ranges::view::transform
        ( []( auto&& ptr )->decltype(auto) { return *ptr; } );
}
