protected:
Node( list_type&& a ) : core( std::move( a ) ) {}

Node( map_type&& m ) : core( std::move( m ) ) {}

public:
Node( Node&& ) = default;
Node( Node& ) = default;
Node( const Node& ) = default;

template< typename T,
          typename = void_t< decltype( leaf_type{ std::declval<T>() } ) > >
Node( T&& t ) : core( leaf_type{ std::forward< T >( t ) } ) {}

template< typename T, typename... Ts>
Node( T&& t, Ts&&... ts ) :
  core( list_type{Node{std::forward<T>(t)},
                  Node{std::forward<Ts>(ts)}...}) {}
