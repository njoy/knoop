Node& pop_front(){
  auto& list = std::get< list_type >( core );
  list.pop_front();
  return *this;
}
