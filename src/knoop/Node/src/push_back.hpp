template< typename T >
Node& push_back( T&& t ){
  auto& list = std::get< list_type >( core );
  list.emplace_back( std::forward<T>(t) );
  return *this;
}

template< typename T, typename... Args >
Node& push_back( T&& t, Args&&... args ){
  auto& list = std::get< list_type >( core );
  list.emplace_back( std::forward<T>(t) );
  return this->push_back( std::forward<Args>(args)... );
}
