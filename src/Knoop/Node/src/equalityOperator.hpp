template< typename T >
Node& operator=( T&& t ){
  *this = Node( t );
  return *this;
}

Node& operator=( Node&& ) = default;
Node& operator=( Node& ) = default;
Node& operator=( const Node& ) = default;
