#include <utility>

template <typename T>
class Stack
{
public:
    Stack() : head(nullptr), stackSize(0){}
    Stack(Stack &&other) : head(std::move(other.head)), stackSize(std::move(other.stackSize)){}        

    ~Stack()
    {
        while (!isEmpty())
            pop();
    }

    template <typename U>
    void push(U &&value)
    {
        auto n = new Node(std::forward<U>(value), head);        
        head = n;
        ++stackSize;
    }

    T &peek()
    {
        if (!head)
            throw StackIsEmptyException();
        return head->value;
    }

    T pop()
    {
        if (!head)
            throw StackIsEmptyException();
        auto value(std::move(head->value)); // move constructor called
        auto temp = head;
        head = temp->next;
        delete temp; // move constructor has turned nullptr
        --stackSize;
        return value;
    }

    bool isEmpty() const
    {
        return !head;
    }

    size_t size() const
    {
        return stackSize;
    }

    class StackIsEmptyException
    {
    };

private:
    struct Node
    {
        Node(T &&v, Node *n): value(v), next(n){} // rvalue only
        // Node(const T &v, Node *n): value(v), next(n){} // rvalue or lvalue
        Node(T &v, Node *n): value(std::move(v)), next(n){} // lvalue only
        T value;
        Node *next;
    };

    Node *head;
    size_t stackSize;
};
