#include <iostream>
/* From this: https://www.geeksforgeeks.org/design-a-stack-with-find-middle-operation/ */
struct Node {
    int value;
    Node* next;
    Node* prev;
};

class Stack {
    Node* head;
    Node* middle;
    int count;
public:
    Stack();
    ~Stack();
    void push(int val);
    void pop(void);
    int top(void);
    Node getMiddleValue(void);
    bool isEmpty(void);
    void print(void);
    void printMiddle(void);
};

Stack::Stack() {
    this->head = NULL;
    this->count = 0;
}

Stack::~Stack() {
    Node* current = this->head;
    while (current) {
        Node* temp = current->next;
        delete current;
        current = temp;
    }
}
bool Stack::isEmpty(void) {
    return (this->head == NULL);
}

void Stack::push(int val) {
    this->count++; 
    Node* new_node = new Node;
    new_node->value = val;
    new_node->prev = NULL;
    if (this->isEmpty()) {
        new_node->next = NULL;
        this->head = new_node;
        this->middle = this->head;
        return;
    }
    Node* current = this->head;
    new_node->next = current;
    current->prev = new_node;
    this->head = new_node;
    if (this->count % 2 == 1) {
        this->middle = this->middle->prev;
    }
}

void Stack::pop(void) {
    if (this->isEmpty()) {
        std::cout << "Empty stack. Nothing to pop." << std::endl;
        return;
    }
    this->count--;
    if (this->head->next) {
        Node* current = this->head;
        this->head = current->next;
        this->head->prev = NULL;
        delete current;
        current = NULL;
        if (this->count % 2 == 0) {
            this->middle = this->middle->next;
        }
    } else { /* only head. Delete it */
        delete this->head;
        this->head = NULL;
        this->middle = NULL;
    }
}

int Stack::top(void) {
    if (this->isEmpty()) {
        std::cout << "Empty stack. No top."  << std::endl;
        return -1;
    }
    return this->head->value;
}

void Stack::print(void) {
    if (this->isEmpty()) {
        std::cout << "Empty stack. Nothing to print" << std::endl;
        return;
    }
    Node* current = this->head;
    while (current) {
        std::cout << "val: " << current->value << std::endl;
        current = current->next;
    }
}

void Stack::printMiddle(void) {
    if (this->isEmpty()) {
        std::cout << "Empty stack. No middle." << std::endl;
        return;
    }
    std::cout << "Middle: " << this->middle->value << std::endl;
}

int main(int argc, char* argv[]) {

    Stack s; 
    s.push(1);
    std::cout << "top:" << s.top() << std::endl;
    s.printMiddle();
    s.push(2);
    std::cout << "top:" << s.top() << std::endl;
    s.printMiddle();
    s.push(3);
    std::cout << "top:" << s.top() << std::endl;
    s.printMiddle();
    s.pop();
    std::cout << "top:" << s.top() << std::endl;
    s.printMiddle();
    s.pop();
    std::cout << "top:" << s.top() << std::endl;
    s.printMiddle();
    s.pop();
    std::cout << "top:" << s.top() << std::endl;
    s.printMiddle();
    return 0;
}