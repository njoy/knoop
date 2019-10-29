template< typename T >
const T& get() const {
  const auto& leaf = std::get< leaf_type >( core );
  return std::get<T>(leaf);
}

template< typename T >
T& get(){
  auto& leaf = std::get< leaf_type >( core );
  return std::get<T>(leaf);
}
