/*
call the MetaData move constructor from within the move constructor for ArrayWrapper?
NO CANNOT
the value of other in the move constructor--it's an rvalue reference, not an rvalue. It's an lvalue
copy constructor is called, not the move constructor.

object has a name and will be lvalue/alive for the entire duration of our function


*/
#include <utility> // for std::move

class MetaData
{
public:
    MetaData (int size, const std::string& name)
        : _name( name )
        , _size( size )
    {}
 
    // copy constructor
    MetaData (const MetaData& other)
        : _name( other._name )
        , _size( other._size )
    {}
 
    // move constructor
    MetaData (MetaData&& other)
        : _name( std::move(other._name) )
        , _size( other._size )
    {}
 
    std::string getName () const { return _name; }
    int getSize () const { return _size; }
    private:
    std::string _name;
    int _size;
};

class ArrayWrapper
{
public:
    // default constructor produces a moderately sized array
    ArrayWrapper ()
        : _p_vals( new int[ 64 ] )
        , _metadata( 64, "ArrayWrapper" )
    {}
 
    ArrayWrapper (int n)
        : _p_vals( new int[ n ] )
        , _metadata( n, "ArrayWrapper" )
    {}
 
    // move constructor
    ArrayWrapper (ArrayWrapper&& other)
        : _p_vals( other._p_vals  )
        , _metadata( std::move(other._metadata) )
    {
        // if _metadata( other._metadata ) calls the move constructor, using 
        //  other._metadata here would be extremely dangerous!
        other._p_vals = NULL;
    }
 
    // copy constructor
    ArrayWrapper (const ArrayWrapper& other)
        : _p_vals( new int[ other._metadata.getSize() ] )
        , _metadata( other._metadata )
    {
        for ( int i = 0; i < _metadata.getSize(); ++i )
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
    MetaData _metadata;
};