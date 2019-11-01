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

const L& get() const {
  const auto& leaf = std::get< leaf_type >( core );
  return std::get<L>(leaf);
}

L& get(){
  auto& leaf = std::get< leaf_type >( core );
  return std::get<L>(leaf);
}
