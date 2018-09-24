#include <iostream> 

struct Node {
    int value;
    Node* next;
};

class Queue {
    Node* front_; 
    Node* rear_;
public:
    Queue();
    ~Queue();
    void enqueue(int val);
    void dequeue(void);
    int peekFront(void); /* return front element */
    int peekRear(void); /* queue rear element (firt) */
    int size(void);
    bool isEmpty(void); 
    void print(void);
};

Queue::Queue() {
    front_ = NULL;
    rear_ = NULL;
}

Queue::~Queue() {
    Node* current = this->front_; 
    while (current) {
        Node* temp = current;
        delete current;
        current = temp->next;
    }
}

void Queue::enqueue(int val) {
/* add the newest item to the rear of the queue */
    Node* new_node = new Node;
    new_node->value = val;
    if (this->rear_ == NULL) {
        new_node->next = NULL;
        this->front_ = new_node;
        this->rear_ = new_node;
        return;
    }
    new_node->next = this->rear_;
    this->rear_ = new_node;
}

void Queue::dequeue(void) {
/* pop the item from the front of the queue */
    if (this->isEmpty()) {
        std::cout << "Empty queue. Nothing to dequeue." << std::endl;
        return;
    }
    Node* temp = this->front_;
    this->front_ = this->front_->next;
    delete temp;
    if (this->front_ == NULL) { /* List is empty now. Set rear_ to empty as well. */
        this->rear_ = NULL;
    }
}

int Queue::peekFront(void) {
    if (this->isEmpty()) {
        std::cout << "Empty queue. No front element to peek." << std::endl;
        return -1;
    }
    return this->front_->value;
}

int Queue::peekRear(void) {
    if (this->isEmpty()) {
        std::cout << "Empty queue. No rear element to peek." << std::endl;
        return -1;
    }
    return this->rear_->value;
}

void Queue::print(void) {
    if (this->isEmpty()) {
        std::cout << "Empty queue. Nothing to print." << std::endl;
        return;
    }
    Node* current = this->rear_;
    while (current) {
        std::cout << "val: " << current->value << std::endl;
        current = current->next;
    }
}

bool Queue::isEmpty(void) {
    return (this->front_ == NULL);
}

int Queue::size(void) {
    int s = 0; 
    Node* current = this->rear_;
    while (current) {
        current = current->next;
        s++;
    }
    return s;
}

int main(int argc, char* argv[]) {

    Queue q;
    q.enqueue(10); 
    q.enqueue(11); 
    q.enqueue(12); 
    std::cout << "size: " << q.size() << std::endl;
    q.print();
    return 0;

}








