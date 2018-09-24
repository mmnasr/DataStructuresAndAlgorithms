#include <iostream>

class twoStacks {
    int *data;
    int top1;
    int top2;
    int size;
    public: 
        twoStacks(int n);
        ~twoStacks();
        void pop1(void);
        void pop2(void);
        void push1(int val); 
        void push2(int val); 
        int getTop1(void);
        int getTop2(void);
        int getSize1(void); 
        int getSize2(void);
        void print1(void);
        void print2(void);
};

twoStacks::twoStacks(int n) {
    this->size = n;
    this->top1 = -1;
    this->top2 = this->size;
    this->data = new int[this->size];
}

twoStacks::~twoStacks() {
    delete this->data;
}

void twoStacks::pop1(void) {
    if (this->top1 >= 0) {
        this->top1--;
        return;
    } 
    std::cout << "Empty stack1. Cannot pop.\n";
    return;
}

void twoStacks::pop2(void) {
    if (this->top2 < this->size) {
        this->top2++;
        return;
    }
    std::cout << "Empty stack2. Cannot pop.\n";
    return;
}

void twoStacks::push1(int val) {
    if (this->top1 < this->top2-1) {
        this->top1++;
        this->data[this->top1] = val;
        return;
    } 
    std::cout << "Stack1 overflow\n";
    return;
}

void twoStacks::push2(int val) {
    std::cout << "top1: " << top1 << std::endl;
    std::cout << "top2: " << top2 << std::endl;
    if (this->top1 < this->top2-1) {
        this->top2--;
        this->data[this->top2] = val;
        return;
    }
    std::cout << "Stack2 overflow\n";
}

int twoStacks::getTop1(void) {
    return this->data[this->top1];
}

int twoStacks::getTop2(void) {
    return this->data[this->top2];
}

void twoStacks::print1(void) {
    if (top1 < 0) {
        std::cout << "Empty stack 1. Nothing to print." << std::endl;
        return;
    }
    for (int i=0; i <= top1; i++) {
        std::cout << "s1: " << this->data[i] << std::endl;
    }
    return;
}

void twoStacks::print2(void) {
    if (top2 >= this->size) {
        std::cout << "Empty stack 2. Nothing to print." << std::endl;
        return;
    }
    for (int i=this->size-1; i >= top2; i--) {
        std::cout << "s2: " << this->data[i] << std::endl;
    }
    return;
}

int twoStacks::getSize1(void) {
    return this->top1+1;
}

int twoStacks::getSize2(void) {
    return this->size-this->top2;
}

int main(int argc, char* argv[]) {
    twoStacks s2(5);
    s2.push1(1);
    s2.push1(2);
    s2.push2(-1);
    s2.push2(-2);
    s2.push2(-3);
    std::cout << "size1: " << s2.getSize1()  << std::endl;
    std::cout << "size2: " << s2.getSize2()  << std::endl;
    s2.push2(-4);
    //s2.push2(-5);
    //s2.push2(-6);
    s2.print1();
    s2.print2();
    //s2.pop1();
    return 0;
}