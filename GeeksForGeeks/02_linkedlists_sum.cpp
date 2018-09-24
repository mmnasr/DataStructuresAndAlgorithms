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
        int getSize(void); 
        Node* getHead(void);
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

Node* LinkedList::getHead(void) {
    
    return this->head;
}

LinkedList sumNumbersFromTwoLists(LinkedList l1, LinkedList l2) {
    /* Assume that l1 (or l2) 
    represents digits of a number (in reverse order): 1->2->3->NULL = 321 */
    /* Example: 
        l1: 1->2->NULL (= 21)
        l2: 5->0->9->1->NULL (= 1905)
    Return a list with digits of the sum (in reverse order)
    Example: should return 
        6->2->9->1->NULL */
    Node* l1_curr = l1.getHead();   
    Node* l2_curr = l2.getHead();   
    LinkedList res; 
    int sum=0;
    int carry=0;
    while (l1_curr || l2_curr) {
        int l1_digit = (l1_curr ? l1_curr->value: 0);
        /* if (l1_curr != NULL) l1_digit = l1_curr->value; else l1_digit = 0; */
        int l2_digit = (l2_curr ? l2_curr->value: 0);
        sum = carry + l1_digit + l2_digit;
        carry = (sum >= 10) ? 1: 0;
        sum = sum % 10;
        res.addValue(sum);         
        if (l1_curr) l1_curr = l1_curr->next;
        if (l2_curr) l2_curr = l2_curr->next;
    }
    if (carry != 0) res.addValue(carry); 
    return res;
}

int main(int argc, char* argv[]) {
    LinkedList l1, l2;
    l1.addValue(0);
    l1.addValue(0);
    l1.addValue(0);
    l1.addValue(1);
    l2.addValue(0);
    l2.addValue(0);
    l2.addValue(1);
    std::cout << "list 1:" << std::endl;
    l1.printValues();
    std::cout << "list 2:" << std::endl;
    l2.printValues();
    
    LinkedList lsum = sumNumbersFromTwoLists(l1, l2); 
    std::cout << "sum digits:" << std::endl;
    lsum.printValues();
    return 0;
}

