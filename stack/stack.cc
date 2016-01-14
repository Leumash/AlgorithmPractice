#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Stack
{
    public:
        void Push(int);
        void Pop();
        int Top();
        bool IsEmpty();
    private:
        vector<int> my_stack;
};

int main()
{
    Stack stack;
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    stack.Push(4);
    stack.Push(5);

    while (!stack.IsEmpty())
    {
        cout << stack.Top() << endl;
        stack.Pop();
    }
}

void Stack::Push(int val)
{
    my_stack.push_back(val);
}

void Stack::Pop()
{
    my_stack.pop_back();
}

int Stack::Top()
{
    return my_stack[my_stack.size()-1];
}

bool Stack::IsEmpty()
{
    return my_stack.empty();
}


