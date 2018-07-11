/* StackMin: How would you design a stack which, in addition to push and pop, has a function min
which returns the minimum element? Push, pop and min should all operate in O(1) time.

type deduction/reference collapsing
perfect forward: cast arg to U&& to keep same lvalue/rvalue arg passing

move: convert arg to rvalue to call constructor, like pass by ref
useful if resource management object (i.e. object w data structure)
dont deep copy array/vector, dont call copy constructor


lvalue reference => copy constructor
rvalue reference => move constructor
    same as pass by reference
    move()

NOT MAKING COPY WHEN PASS AS ARG
1. explicitly pass in rvalue => move contructor called to construct arg
2. pass by reference => call NO constructor at all
3. std::move() => move constructor called + object destroyed


g++ -std=c++14 stackmin.cpp -o stackmin
*/
#include <iostream>
#include "stack.hpp"

template<typename T>
class StackMin
{
public:
    template<typename U>

    // U && => universal reference w type deduction/reference collapsing 
    // => not neccessaily rvalue reference
    void push(U &&value) 
    {   
        // perfect forwarding: maintain same lvalue/rvalue arg
        if (minStack.isEmpty() || value <= minStack.peek())
            minStack.push(std::forward<U>(value));
        stack.push(std::forward<U>(value));
    }

    T &peek(){return stack.peek();}
    T &min(){return minStack.peek();}

    T pop()
    {
        auto value = stack.pop();
        if (value == min())
            minStack.pop();
        return value;
    }

    bool isEmpty()
    {
        return stack.isEmpty();
    }

private:
    Stack<T> stack;
    Stack<T> minStack;
};

int main()
{
    StackMin<int> stack;
    // stack.push(9); // rvalue test
    // stack.push(10);

    for (auto v : {5, 10, 4, 9, 3, 3, 8, 2, 2, 7, 6}) // lvalue test
    {
        stack.push(v); 
        std::cout << "Pushed value: " << v << ", min value: " << stack.min() << std::endl;
    }
    while (!stack.isEmpty())
    {
        auto v = stack.pop();
        std::cout << "Popped value: " << v;
        if (stack.isEmpty())
            std::cout << ", stack is empty" << std::endl;
        else
            std::cout << ", min value: " << stack.min() << std::endl;
    }
    return 0;
}