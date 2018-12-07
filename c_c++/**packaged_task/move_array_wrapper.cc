/*
https://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html

1. The parameter is a non-const rvalue reference
2. other._p_vals is set to NULL

The second observation explains the first--we couldn't set 
other._p_vals to NULL if we'd taken a const rvalue reference.

Why move constructor set pointer NULL ?
rhs temp object destructor runs when goes out of scope and free temp object’s pointer
However since we shallow copy such pointer into lhs, when lhs object destroyed, free pointer twice


*/
class ArrayWrapper
{
public:
    // default constructor produces a moderately sized array
    ArrayWrapper ()
        : _p_vals( new int[ 64 ] )
        , _size( 64 )
    {}
 
    ArrayWrapper (int n)
        : _p_vals( new int[ n ] )
        , _size( n )
    {}
 
    // move constructor
    ArrayWrapper (ArrayWrapper&& other)
        : _p_vals( other._p_vals  )
        , _size( other._size )
    {
        other._p_vals = NULL;
        other._size = 0;
    }
 
    // copy constructor
    ArrayWrapper (const ArrayWrapper& other)
        : _p_vals( new int[ other._size  ] )
        , _size( other._size )
    {
        for ( int i = 0; i < _size; ++i )
        {
            _p_vals[ i ] = other._p_vals[ i ];
        }
    }
    ~ArrayWrapper ()
    {
        delete [] _p_vals;
    }
 
private:
    int *_p_vals;
    int _size;
};