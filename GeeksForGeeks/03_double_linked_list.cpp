#include <iostream> 

struct Node {
    int value; 
    Node* next; 
    Node* prev; 
};

class DLinkedList {
    Node* head; 
    public:
        DLinkedList();
        ~DLinkedList();
        void push(int val); /* add at the head */
        void append(int val); /* add to the end */
        void printValues(void); /* print all values */
        void insertBefore(int v, int v_insert);
        void delValue(int v); /* delete a value */
        void reverse(void); /* reverse a list */
};

DLinkedList::DLinkedList() {
    this->head = NULL;   
}

DLinkedList::~DLinkedList() {
    Node* current = this->head;
    while (current) {
        Node* temp = current->next;
        delete current;
        current = temp;
    }
}

void DLinkedList::push(int val) {
/* add a value at head (top) of the list */
    Node* new_node = new Node;
    Node* old_head = this->head;
    new_node->value = val;
    new_node->prev = NULL;
    new_node->next = old_head;
    if (old_head != NULL) {
        old_head->prev = new_node;
    }
    this->head = new_node;
}

void DLinkedList::append(int val) {
/* add a value at the end of the list */
    Node* new_node = new Node;
    new_node->value = val; 
    new_node->next = NULL;
    if (this->head == NULL) {
        new_node->prev = NULL;
        this->head = new_node;
        return;
    }
    Node* current = this->head; 
    while (current->next) {
        current = current->next;
    }
    new_node->prev = current;
    current->next = new_node;
    return;
}

void DLinkedList::printValues(void) {
    Node* current = this->head;
    while (current) {
        std::cout << current->value <<", " << std::endl;
        current = current->next;
    }
    std::cout << std::endl;
}

void DLinkedList::insertBefore(int v, int v_ins) {
    /* inserts a new value v_ins before a given node (w/ given value v) */
    Node* new_node = new Node;
    new_node->value = v_ins;
    if (this->head == NULL) {
        new_node->next = NULL;
        new_node->prev = NULL;
        this->head = new_node;
        return;
    }
    Node* current = this->head;
    while (current && current->value != v) {
        current = current->next;
    }
    if (current->value == v) {
        if (current->prev == NULL) { /* only head exists in current list. */
            new_node->next = this->head;
            new_node->prev = NULL;
            this->head = new_node;
            return;
        }
        new_node->next = current;
        new_node->prev = current->prev;
        current->prev = new_node;
        return;
    }
    std::cout << "Could not find the given value in the list" << std::endl;
}

void DLinkedList::delValue(int v) {
    if (this->head == NULL) return;
    Node* current = this->head;
    while (current != NULL && current->value != v) {
        current = current->next;
    }
    if (current == NULL) {
        std::cout << "Could not find the value to be deleted in the list: " << v << std::endl;
        return;
    }
    Node* prev = current->prev; 
    Node* next = current->next; 
    if (prev) {
        prev->next = current->next;
    } 
    if (next) {
        next->prev = current->prev; 
    }
    delete current;
}

void DLinkedList::reverse(void) {
    if (this->head == NULL || this->head->next == NULL) return;
    Node* current = this->head;
    Node* temp=NULL;
    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    std::cout << "val end: " << temp->prev->value << std::endl;
    
    this->head = temp->prev;
}

int main(int argc, char* argv[]) {
    DLinkedList l1;
    l1.append(1); 
    l1.append(2);
    std::cout << "********" << std::endl;
    //l1.reverse();
    l1.printValues();
    l1.insertBefore(1, 3);
    //l1.printValues();
    l1.delValue(2);
    std::cout << "****" << std::endl;
    l1.printValues();
    
    return 0;
}
