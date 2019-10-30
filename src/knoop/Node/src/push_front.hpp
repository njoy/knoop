template< typename T >
Node& push_front( T&& t ){
  auto& list = std::get< list_type >( core );
  list.emplace_front( std::forward<T>(t) );
  return *this;
}

template< typename T, typename... Args >
Node& push_front( T&& t, Args&&... args ){
  auto& list = std::get< list_type >( core );
  this->push_front( std::forward<Args>(args)... );
  return this->push_front( std::forward<T>(t) );
}
