#include <iostream>
#include <stack>
#include <list>

class SetOfStacks {
private:
    static const int single_stack_capacity=2;
    std::list<std::stack<int> > stacks;
    void printStackPrivate(std::stack<int> st);
    std::stack<int>* getLastStackPrivate(void);
    
public:
    SetOfStacks(void); 
    void push(int k);
    void pop(void);
    int top(void);
};

SetOfStacks::SetOfStacks(void) {
    std::stack<int> firstStack; 
    this->stacks.push_back(firstStack);
}

std::stack<int>* SetOfStacks::getLastStackPrivate(void) {
    return &this->stacks.front();
}

void SetOfStacks::push(int k) {
    std::stack<int>* last_st = this->getLastStackPrivate();
    last_st->push(k);
    if (last_st->size() > single_stack_capacity) {
        std::stack<int> newStack;
        this->stacks.push_back(newStack);
    }
}

void SetOfStacks::pop(void) {
    std::stack<int>* last_st = this->getLastStackPrivate();
    last_st->pop();
    if (last_st->size() == 0) 
        this->stacks.pop_front();
}

int SetOfStacks::top(void) {
    std::stack<int>* last_st = this->getLastStackPrivate();
    if (last_st->size() == 0) {
        std::cout << "Empty stack" << std::endl;
        return -100000;
    }
    return last_st->top();
}

int main() {
    SetOfStacks s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.pop();
    std::cout << s.top() << std::endl;
    s.push(-1);
    std::cout << s.top() << std::endl;
    s.pop();
    s.pop();
    s.pop();
    std::cout << s.top() << std::endl;
    return 0;
}