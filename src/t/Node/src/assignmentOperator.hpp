template< typename T >
Node& operator=( T&& t ){ return *this = Node( t ); }
Node& operator=( Node&& ) = default;
Node& operator=( Node& ) = default;
Node& operator=( const Node& ) = default;
