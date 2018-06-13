const Node& front() const {
  return  std::experimental::get< list_type >( core ).front();
}

Node& front() {
  return  std::experimental::get< list_type >( core ).front();
}
