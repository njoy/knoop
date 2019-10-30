const Node& back() const {
  return std::get< list_type >( core ).back();
}

Node& back() {
  return std::get< list_type >( core ).back();
}
