auto list() {
  auto& list = std::experimental::get< list_type >( core );

  return list | ranges::view::all;
}