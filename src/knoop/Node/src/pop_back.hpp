Node& pop_back(){
  auto& list = std::experimental::get< list_type >( core );
  list.pop_back();
  return *this;
}
