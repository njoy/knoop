const Node& front() const {
  return  std::get< list_type >( core ).front();
}

Node& front() {
  return  std::get< list_type >( core ).front();
}
