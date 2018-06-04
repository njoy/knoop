protected:
Node( list_type&& a ):
  core( std::move( a ) )
{ }

Node( map_type&& m ):
  core( std::move( m ) )
{ }

public:
template< typename T, 
          typename L=void_t< decltype(leaf_type{std::declval<T>()}) > >
Node( T&& t ):
  core( leaf_type{ std::forward< T >( t ) } )
{ }

Node( Node&& ) = default;
Node( Node& ) = default;
Node( const Node& ) = default;
