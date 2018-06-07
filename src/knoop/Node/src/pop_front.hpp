Node& pop_front(){
  auto& list = std::experimental::get< list_type >( core );
  list.pop_front();
  return *this;
}
