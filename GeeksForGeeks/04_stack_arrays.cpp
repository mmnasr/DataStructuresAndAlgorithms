#include <iostream> 

class Stack {
    int size; /* current array size */
    int capacity; /* capacity > size to avoid re-allocating memory w/ every insertion */
    int* data; 
    bool updateCapacityPrivate(void); 
    public: 
        Stack();
        ~Stack();
        bool push(int val);
        int pop(void); 
        bool isEmpty(void); 
        int getSize(void); 
        void print(void);
}; 

Stack::Stack() {
    this->size = 0;
    this->capacity = 2;
    this->data = new int[this->capacity];
}

Stack::~Stack() {
    delete data;
}

bool Stack::updateCapacityPrivate(void) {
    this->capacity = 1.25*this->capacity + 1; 
    int* temp = new int[this->capacity];
    if (temp == NULL) return false;
    for (int i=0; i < this->size; i++) temp[i] = this->data[i];
    int* delPtr = this->data;
    delete []delPtr;
    this->data = temp;
    delPtr = NULL;
    return true;
}

bool Stack::push(int val) {
    this->data[this->size] = val;
    this->size++;
    if (this->size > this->capacity) {
        bool success = updateCapacityPrivate();
        if (!success) {
            std::cout << "Memory error. Could not expand stack to new capacity: " << this->capacity;
            return false;
        }
    }
    return true;
}

void Stack::print(void) {
    if (isEmpty()) std::cout << "Empty stack. Nothing to list.\n";
    for (int i=0; i < this->size; i++) {
        std::cout << "value: " << this->data[i] << std::endl;
    }
    return;
}

int Stack::getSize(void) {
    return this->size;
}

int Stack::pop(void) {
    if (this->size) {
        int x = this->data[(this->size--) -1];
        return x;
    } else {
        std::cout<<"Warning. Empty stack. Returning 0." << std::endl;
        return 0;
    }
}

bool Stack::isEmpty(void) {
    if (this->size) return true;
    return false;
}

int main(int argc, char *argv[]) {
    Stack s; 
    s.push(10);
    s.push(2);
    s.push(5);
    std::cout << "size: " << s.getSize() << std::endl;
    s.print();
    s.pop();
    s.pop();
    s.pop();
    s.print();
    std::cout << "size: " << s.getSize() << std::endl;
    std::cout << "isEmpty: " << s.isEmpty() << std::endl;
    return 0;
}