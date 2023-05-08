#include <iostream>
#include <stack>
#include <stdexcept>

class StackWithMaxElement
{
    private:
        std::stack<int> mainStack;
        std::stack<int> maxStack;

    public:
        void push(int i)
        {
            mainStack.push(i);
            
            if(maxStack.empty() || i >= maxStack.top())
            {
                maxStack.push(i);
            }
        }

        void pop()
        {
            if(mainStack.empty())
            {
                throw std::runtime_error("Stack is empty");
            }

            if(mainStack.top() == maxStack.top())
                maxStack.pop();
            
            mainStack.pop();
        }

        int top()
        {
            if(mainStack.empty())
            {
                throw std::runtime_error("Stack is empty");
            }

            return mainStack.top();
        }

        int max()
        {
            if(maxStack.empty())
            {
                throw std::runtime_error("Stack is empty");
            }
            
            return maxStack.top();
        }

        bool empty()
        {
            return mainStack.empty();
        }
};

int main()
{
    StackWithMaxElement stack;

    stack.push(1);
    stack.push(5);
    stack.push(4);

    std::cout<<stack.max();
}