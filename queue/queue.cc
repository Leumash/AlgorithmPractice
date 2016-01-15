#include <iostream>
#include <cstdlib>

using namespace std;

struct Node
{
    int val;
    Node* next;
};

class Queue
{
    public:
        Queue();
        bool IsEmpty();
        void Pop();
        void Push(int);
        int Top();
    private:
        Node* push_node;
        Node* pop_node;
};

int main()
{
    Queue queue;
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);
    queue.Push(4);
    queue.Push(5);
    queue.Push(6);

    while (!queue.IsEmpty())
    {
        if (queue.Top() == 3)
        {
            queue.Push(7);
        }

        cout << queue.Top() << endl;;

        queue.Pop();
    }
}

Queue::Queue()
{
    push_node = NULL;
    pop_node = NULL;
}

bool Queue::IsEmpty()
{
    return pop_node == NULL;
}

void Queue::Pop()
{
    Node* to_delete = pop_node;
    pop_node = pop_node->next;
    delete to_delete;
}

void Queue::Push(int val)
{
    Node* new_node = new Node();
    new_node->next = NULL;
    new_node->val = val;

    if (pop_node == NULL)   // Empty linked list
    {
        pop_node = push_node = new_node;
    }
    else
    {
        push_node->next = new_node;
        push_node = new_node;
    }
}

int Queue::Top()
{
    return pop_node->val;
}

