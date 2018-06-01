auto list() {
  auto& list = std::experimental::get< array_type >( core );

  return list | ranges::view::indirect;
}
