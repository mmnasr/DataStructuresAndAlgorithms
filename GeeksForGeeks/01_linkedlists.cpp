#include <iostream>

struct Node {
    int value;
    Node* next;
};

class LinkedList {
    Node* head;
    void swapNodePrivate(Node*& n1, Node*& n2);
    int getSizeRecursivePrivate(Node* node);
    public:
        LinkedList();
        ~LinkedList();
        void printValues(void); /* list all values of the list */
        void addValue(int val); /* add a new value to the list */
        void delValue(int val); /* delete a given value from a list */
        void pushValue(int val); /* push a new value to the head of the list */
        int getSize(void); 
        int getSizeRecursive(void);
        void delValueAtIndex(int index); /* delete the node at given position (index=0 correspond to head) */
        void swap(int v1, int v2);
        void swap_better(int v1, int v2);
        void reverse(void); /* reverse linked list */
        bool hasLoop(void);
        void rotate(int k); /* rotate the list by k */
};

LinkedList::LinkedList() {
    head = NULL;    
}

LinkedList::~LinkedList() {
    /* free up memory */
    if (this->head != NULL) {
        Node* current = this->head;
        while (current->next != NULL) {
            current = current->next;
        }
    }
}

void LinkedList::printValues(void) {
    Node* current = this->head;
    while (current != NULL) {
        std::cout << "val: " << current->value << std::endl;
        current = current->next;
    }
}

void LinkedList::addValue(int val) {
    Node* new_node = new Node;
    new_node->next = NULL; 
    new_node->value = val;   
     
    if (this->head != NULL) {
        Node* current = head; 
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    } else {
        this->head = new_node;
    }
}

void LinkedList::delValue(int val) {
    Node* current = this->head; 
    Node* previous = this->head;
    while(current != NULL && current->value != val) {
        previous = current; 
        current = current->next; 
    }
    if (current == NULL) {
        std::cout << "Warning. Could not find the given value "<< val <<" in the list."<< std::endl;
        return;
    }
    Node* del_node = current;
    previous->next = current->next;
    if (del_node == this->head) {
        this->head = this->head->next;
        previous = NULL;
    }
    delete del_node;
}

int LinkedList::getSize(void) {
    
    Node* current = this->head;
    int size = 0; 
    while (current != NULL) {
        current = current->next; 
        size++; 
    }
    return size;
}

void LinkedList::pushValue(int val) {
    
    Node* new_node = new Node;
    new_node->value = val;
    new_node->next = this->head;
    this->head = new_node;
}

void LinkedList::delValueAtIndex(int index) {
    if (index == 0) {
        Node* del_node = this->head; 
        this->head = this->head->next; 
        delete del_node;
        return;
    }
    Node* current = this->head;
    for (int i=0; i<index-1 && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL || current->next == NULL) {
        std::cout << "Cannot delete at given position "<< index << ". Index position greater than list size." << std::endl;
        return;
    }
    Node* del_node = current->next; 
    delete del_node;
    current->next = current->next->next;
}

int LinkedList::getSizeRecursive(void) {
    int size = this->getSizeRecursivePrivate(this->head); 
    return size;
}

int LinkedList::getSizeRecursivePrivate(Node* node) {
    if (node == NULL) return 0;    
    return (1 + this->getSizeRecursivePrivate(node->next));
}

void LinkedList::swap(int v1, int v2) {
    if (v1 == v2) return; 
    Node* currX = this->head; 
    Node* prevX = NULL; 
    while (currX != NULL && currX->value != v1) {
        prevX = currX; 
        currX = currX->next; 
    }
    Node* currY = this->head; 
    Node* prevY = NULL; 
    while (currY != NULL && currY->value != v2) {
        prevY = currY; 
        currY = currY->next; 
    }
    if (currX == NULL) {
        std::cout << "Value 1: " << v1 << " not found in the list to swap." << std::endl;
        return;
    }
    if (currY == NULL) {
        std::cout << "Value 2: " << v2 << " not found in the list to swap." << std::endl;
        return;
    }
    if (prevX == NULL) { /* X is a head node */
        this->head = currY; 
    } else {
        prevX->next = currY;
    }
    if (prevY == NULL) { /* Y is a head node */
        this->head = currX;
    } else {
        prevY->next = currX;
    }
    Node* temp = currY->next; 
    currY->next = currX->next; 
    currX->next = temp;
}
void LinkedList::swapNodePrivate(Node*& n1, Node*& n2) {
    Node* temp = n1; 
    n1 = n2; 
    n2 = temp;
}

void LinkedList::swap_better(int v1, int v2) {
    if (v1 == v2) return; 
    Node* current = this->head;
    Node* currX=NULL;
    Node* currY=NULL; 
    while (current) {
        if (current->value == v1) {
            currX = current;            
        } else if (current->value == v2) {
            currY = current; 
        }
        current = current->next; 
    }
    if (currX && currY) {
        this->swapNodePrivate(currX, currY); 
        this->swapNodePrivate(currX->next, currY->next); 
        std::cout << "here:" << currX->value << std::endl;
        return; 
    }
    std::cout << "Could not find given values in the list to swap." << std::endl;
}

void LinkedList::reverse(void) {

    Node* prev=NULL;
    Node* current=this->head;
    Node* next=current->next;
    while (current != NULL) {
        next = current->next; 
        current->next = prev;
        prev = current;
        current = next;
    }
    this->head = prev;
}

bool LinkedList::hasLoop(void) {    
    if (this->head == NULL ||  this->head->next == NULL) return false;
    Node* fast=this->head;
    Node* slow=this->head;
    slow = slow->next; 
    fast = fast->next->next;
    if (fast->next == NULL) return false;
    while (fast && fast->next) {
        if (slow == fast) return true;
        slow = slow->next;
        fast = fast->next->next;
    }
    return false;
}

void LinkedList::rotate(int k) {

    if (k == 0) return; 
    int count = 1; 
    Node* current = this->head;
    while (count < k && current != NULL) {
        current = current->next; 
        count++;
    }
    /* k is greater than the list size. Don't rotate. */
    if (current == NULL) return; 
    Node* kthNode = current;
    while (current->next != NULL) 
        current = current->next;
    current->next = this->head;
    this->head = kthNode->next;
    kthNode->next = NULL;
}

int main(int argc, char* argv[]) {
    LinkedList l1;
    l1.addValue(2);
    l1.addValue(5);
    l1.addValue(3);
    l1.addValue(9);
    //l1.pushValue(11);
    l1.printValues();
    //l1.delValueAtIndex(4);
    //l1.swap(2,5);
    l1.swap_better(2,5); 
    std::cout << "After swap" << std::endl;
    l1.printValues();
    std::cout << "\nsize: " << l1.getSizeRecursive() << std::endl;
    l1.reverse();
    std::cout << "After reverse" << std::endl;
    l1.printValues();
    std::cout << "After rotate 2:" << std::endl;
    l1.rotate(1); 
    l1.printValues();
    return 0;
}

