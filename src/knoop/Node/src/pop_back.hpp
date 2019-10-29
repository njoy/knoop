Node& pop_back(){
  auto& list = std::get< list_type >( core );
  list.pop_back();
  return *this;
}
