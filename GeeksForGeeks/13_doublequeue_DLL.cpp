#include <iostream>

struct Node {
    int value;
    Node* next;
    Node* prev;
};

/* rear-> 1 -> 2 -> ... -> n -> front */
class Dqueue {
    Node* front;
    Node* rear;
public:
    Dqueue();
    ~Dqueue();
    void insertFront(int val); 
    void insertRear(int val);
    int peekFront(void);
    int peekRear(void);
    void dequeueFront(void);
    void dequeueRear(void);
    bool isEmpty(void);
    int size(void);
    void print(void); 
};

Dqueue::Dqueue() {
    this->front = NULL;
    this->rear = NULL;
}

Dqueue::~Dqueue() {
    Node* current = this->rear;
    while (current) {
        Node* temp = current; 
        delete temp;
        current = current->next;
        temp = NULL;
    }
}

bool Dqueue::isEmpty(void) {
    return (this->rear == NULL);
}

void Dqueue::insertRear(int val) {
    Node* new_node = new Node;
    new_node->value = val;
    new_node->prev = NULL;
    if (this->isEmpty()) {
        new_node->next = NULL;
        this->rear = new_node;
        this->front = new_node;
        return;
    }
    new_node->next = this->rear;
    this->rear->prev = new_node;
    this->rear = new_node;
    if (this->front->prev == NULL) {
        this->front->prev = this->rear;
    }
    std::cout << "here***********" <<std::endl;
    //this->print();
    std::cout << "inside front: " << this->peekFront() << std::endl;
    std::cout << "front prev: " << this->front->prev->value << std::endl;
    std::cout << "inside rear: " << this->peekRear() << std::endl;
}

void Dqueue::insertFront(int val) {
    Node* new_node = new Node;
    new_node->value = val;
    new_node->next = NULL;
    if (this->isEmpty()) {
        new_node->prev = NULL;
        this->front = new_node;
        this->rear = new_node;
        return;
    }
    new_node->prev = this->front;
    this->front->next = new_node;
    this->front = new_node;
    if (this->rear->next == NULL) {/* only one node is in the list */
        this->rear->next = this->front;
    }
}

int Dqueue::peekFront(void) {
    if (this->isEmpty()) {
        std::cout << "Empty Dqueue. Nothing to peek (front)." << std::endl;
        return -1;
    }
    return this->front->value;
}

int Dqueue::peekRear(void) {
    if (this->isEmpty()) {
        std::cout << "Empty Dqueue. Nothing to peek (rear)." << std::endl;
        return -1;
    }
    return this->rear->value;
}

void Dqueue::dequeueRear(void) {
    if (this->isEmpty()) {
        std::cout << "Empty Dqueue. Cannot dequeue (rear)." << std::endl;
        return;
    }
    Node* current = this->rear;
    this->rear = this->rear->next;
    if (this->rear == NULL) {
        this->front = NULL;
    } else {
        this->rear->prev = NULL;
    }
    delete current;
    current = NULL;
    std::cout << "*******YOYO*************" << std::endl;
    this->print();
}

void Dqueue::dequeueFront(void) {
    if (this->isEmpty()) {
        std::cout << "Empty Dqueue. Cannot deuque (front)." << std::endl;
        return;
    }
    Node* current = this->front;
    this->front = this->front->prev;
    if (this->front == NULL) {
        this->rear = NULL;
        std::cout << "GOOZ" << std::endl;
    } else {
        this->front->next = NULL;
    }
    std::cout << "--->current value: " << current->value << std::endl;
    std::cout << "---> peek front: " << this->peekFront() << std::endl;
    delete current;
    current = NULL;
}

void Dqueue::print(void) {
    if (this->isEmpty()) {
        std::cout << "Empty Dqueue. Nothing to print. " << std::endl;
        return;
    }
    Node* current = this->rear; 
    while (current) {
        std::cout << "val: " << current->value << std::endl;
        current = current->next;
    }
}

int Dqueue::size(void) {
    Node* current = this->rear; 
    int s = 0;
    while (current) {
        s++;
        current = current->next;
    }
    return s;
}

int main(int argc, char *argv[]) {

    Dqueue dq;
    dq.insertRear(1); 
    dq.insertRear(2); 
    dq.insertRear(3); 
    std::cout << "Size: " << dq.size() << std::endl;
    std::cout << "Peekfront: " << dq.peekFront() << std::endl;
    dq.print();
    dq.dequeueRear(); 
    dq.dequeueRear(); 
    dq.dequeueFront(); 
    std::cout << "***DONE1****" << std::endl;
    dq.print();
    dq.dequeueFront(); 
    std::cout << "***DONE2****" << std::endl;
    dq.dequeueFront(); 
    std::cout << "***DONE3****" << std::endl;
    //dq.dequeueFront(); 
    //dq.dequeueFront(); 
    std::cout << "***DONE4****" << std::endl;
    std::cout << "Size: " << dq.size() << std::endl;
    dq.print();
    //dq.dequeueFront(); 
    //dq.dequeueFront(); 
    std::cout << "front: " << dq.peekFront() << std::endl;
    std::cout << "rear: " << dq.peekRear() << std::endl;
    std::cout << "***DONE****" << std::endl;
    return 0;
}