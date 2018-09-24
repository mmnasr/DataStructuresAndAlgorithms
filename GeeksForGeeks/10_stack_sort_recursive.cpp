#include <iostream>
#include <stack>

class Stack {
    int top; 
    int capacity;
    int *data;
    void updateCapacityPrivate();

public:
    Stack();
    ~Stack();
    void doPush(int val);
    void doPop(void);
    int doTop(void);
    int size(void);
    bool isEmpty(void);
    void print(void);
    void sortedInsert(int val, bool ascending);
    void sort(bool ascending);
};

Stack::Stack() {

    this->data = new int[2];
    this->top = -1;
    this->capacity = 2;
    return;
}

Stack::~Stack() {
    delete []data;
    this->data = NULL;
    return;
}

void Stack::updateCapacityPrivate(void) {
    this->capacity = (int)1.25*this->capacity + 1;
    int* data_exp = new int[this->capacity];
    for (int i=0; i <= this->top; i++) {
        data_exp[i] = this->data[i];
    }
    int* delPtr = this->data;
    this->data = data_exp;
    delete []delPtr;
    delPtr = NULL;
    return;
}

void Stack::doPush(int val) {
    this->top++;
    this->data[this->top] = val;
    if (this->top >= this->capacity-2) {
        this->updateCapacityPrivate();
    }
}

int Stack::doTop(void) {
    if (!isEmpty()) {
        return this->data[this->top];
    }
    std::cout << "Empty stack. No top value." << std::endl;
    return -1;
}

void Stack::doPop(void) {
    if (!isEmpty()) {
        this->top--;
        return;
    }
    std::cout << "Empty stack. Cannot pop." << std::endl;
}

void Stack::print(void) {
    if (!isEmpty()) {
        for (int i=0; i <= this->top; i++) {
            std::cout << "val: " << this->data[i] << std::endl;
        }
        return;
    }
    std::cout << "Empty stack. No values to print." << std::endl;
}

bool Stack::isEmpty(void) {
    return (this->top < 0);
}

void Stack::sortedInsert(int val, bool ascending) {
    /* insert a new element such that it appears in the right location in the stack in the ascending order */
    if (ascending) {
        if (this->isEmpty() || val > this->doTop()) {
            this->doPush(val);
            return;
        } 
    } else {
        if (this->isEmpty() || val <= this->doTop()) {
            this->doPush(val);
            return;
        }
    }
    int lastTop = this->doTop();
    this->doPop();
    this->sortedInsert(val, ascending);
    this->doPush(lastTop);
}

void Stack::sort(bool ascending) {
    /* sort the stack recursively */
    if (!this->isEmpty()) {
        int temp = this->doTop();
        this->doPop();
        this->sort(ascending);
        this->sortedInsert(temp, ascending);
    }
}

int main(int argc, char* argv[]) {
    Stack s;
    s.doPush(3);
    s.doPush(2);
    s.doPush(1);
    s.doPush(4);
    s.doPush(6);
    s.doPush(5);
    //s.print();
    //s.sortedInsert(-5);
    s.sort(false);
    //s.doPop();
    //s.doPop();
    //s.doPop();
    s.print();

    return 0;
}
