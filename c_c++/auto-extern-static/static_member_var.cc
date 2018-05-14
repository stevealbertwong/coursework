/*
http://www.learncpp.com/cpp-tutorial/811-static-member-variables/

Static member variable: shared by all instances of SAME class
like global variable of all instances of same class

*/
class Something
{
public:
    static int s_value;
};
 
 // normally cannot do it unless static
int Something::s_value = 1;
 
int main()
{
    Something first;
    Something second;
 
    first.s_value = 2;
 
    std::cout << first.s_value << '\n';
    std::cout << second.s_value << '\n';
    return 0;
}