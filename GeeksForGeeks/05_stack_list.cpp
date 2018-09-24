#include <iostream>

struct Node {
    int value; 
    Node* next;
};

class Stack {
    Node* root;
    public:
        Stack();
        ~Stack();
        bool push(int v);
        int pop(void);
        int getSize();
        bool isEmpty();
        void print(void);
};

Stack::Stack() {
    this->root = NULL;
}

Stack::~Stack() {
    Node* current = this->root;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

bool Stack::push(int v) {
    Node* new_node = new Node;
    if (new_node == NULL) {
        std::cout << "Error. Could not push new value." << std::endl;
        return false;
    }
    new_node->value = v;
    if (this->root == NULL) {
        new_node->next = NULL;
        this->root = new_node;
        return true;
    }
    Node* temp = this->root;
    new_node->next = temp;
    this->root = new_node; 
    return true;
}

void Stack::print(void) {
    Node* current = this->root;
    if (current == NULL) { 
        std::cout << "Empty stack. Nothing to print." << std::endl;
        return;
    }
    while (current) {
        std::cout<< "val: " << current->value << std::endl;
        current = current->next;
    }
}

int Stack::getSize(void) {
    Node* current = this->root; 
    int size = 0; 
    while (current) {
        current = current->next;
        size++; 
    }
    return size;
}

int Stack::pop(void) {
    if (this->root == NULL) {
        std::cout << "Empty stack. Nothing to pop\n"; 
        return 0;   
    }
    Node* current = this->root;
    this->root = this->root->next;
    int pop_val = current->value; 
    delete current; 
    current = NULL;
    return pop_val;
}

int main(int argc, char *argv[]) {
    Stack s;
    bool success = s.push(10); 
    success = s.push(11); 
    success = s.push(12); 
    success = s.push(13); 
    s.print();
    s.pop();
    s.pop();
    s.pop();
    s.pop();
    s.print();
    return 0;
}