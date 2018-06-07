template< typename T >
const T& get() const {
  const auto& leaf = std::experimental::get< leaf_type >( core );
  return std::experimental::get<T>(leaf);
}

template< typename T >
T& get(){
  auto& leaf = std::experimental::get< leaf_type >( core );
  return std::experimental::get<T>(leaf);
}
