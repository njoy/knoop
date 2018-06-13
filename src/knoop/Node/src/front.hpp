const Node& front() const {
  auto& list = std::experimental::get< list_type >( core );
  return list.front();
}

Node& front() {
  auto& list = std::experimental::get< list_type >( core );
  return list.front();
}
