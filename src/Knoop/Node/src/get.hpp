template< typename T >
T get(){
  auto& leaf = std::experimental::get< leaf_type >( core );
  return std::experimental::get<T>(leaf);
}
