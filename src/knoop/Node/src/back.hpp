const Node& back() const {
  auto& list = std::experimental::get< list_type >( core );
  return list.back();
}

Node& back() {
  auto& list = std::experimental::get< list_type >( core );
  return list.back();
}
