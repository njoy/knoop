auto list() {
  auto& list = std::get< list_type >( core );
  return list | ranges::view::all;
}

auto list() const {
  const auto& list = std::get< list_type >( core );
  return list | ranges::view::all;
}
