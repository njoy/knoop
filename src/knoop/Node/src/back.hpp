const Node& back() const {
  return std::experimental::get< list_type >( core ).back();
}

Node& back() {
  return std::experimental::get< list_type >( core ).back();
}
