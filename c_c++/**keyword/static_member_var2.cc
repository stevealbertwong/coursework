/*
http://www.learncpp.com/cpp-tutorial/811-static-member-variables/

static members exist even if no objects of the class have 
been instantiated! Much like global variables, they are 
created when the program starts, and destroyed when the 
program ends.
*/

class Something
{
public:
    static int s_value; // declares the static member variable
};
 
int Something::s_value = 1; // defines the static member variable (we'll discuss this section below)
 
int main()
{
    // note: we're not instantiating any objects of type Something
 
    Something::s_value = 2;
    std::cout << Something::s_value << '\n';
    return 0;
}