#include <iostream>
#include <stack>

template <class eleT>
eleT get_and_remove_bottom(std::stack<eleT> &srcStack)
{
    auto top = srcStack.top();
    srcStack.pop();
    if (srcStack.empty()) 
    {
        return top;
    }
    else
    {
        auto bottom = get_and_remove_bottom(srcStack);
        srcStack.push(top);
        return bottom;
    }
}

template <class eleT>
void reverse_stack(std::stack<eleT> &srcStack)
{
    if (!srcStack.empty())
    {
        auto bottom = get_and_remove_bottom(srcStack);
        reverse_stack(srcStack);
        srcStack.push(bottom);
    }
}

template <class eleT>
void print_stack(std::stack<eleT> srcStack /* take the value to make a copy */)
{
    std::cout << "stack content: ";
    while (!srcStack.empty())
    {
        std::cout << srcStack.top() << " ";
        srcStack.pop();
    }
    std::cout << std::endl;
}

int main()
{
    std::stack<int> myStack;
    for (int i = 1; i < 6; ++i)
    {
        myStack.push(i); 
    }

    print_stack(myStack);
    reverse_stack(myStack);
    print_stack(myStack);

    return 0;
}
