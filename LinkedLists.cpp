/* Linked Lists: https://en.wikipedia.org/wiki/Linked_list */
/* A C++ implementation of linked lists with pointers. */
/* By: Mohamad Nasr-Azadani, mmnasr@gmail.com */
/***************************************************************************************/
/***************************************************************************************/
/* Operations + and - are also defined: */
/*  +: union of two lists */
/*  -: subtract (set operations) of two lists */

#include <iostream>
#include <cstdlib>

/* Struct node */
struct Node {
    int value;  /* value to be stored in current node */
    Node *next; /* pointer to next node in the list */
};
typedef struct Node* NodePtr;

/* Class demonstrating list */
class List {
    NodePtr head; /* Pointer to the head of the list */
public:
    List();
    ~List();
    void addValue(int value);
    void delValue(int value);
    bool hasValue(int value);
    void printList(void);
    int getSize(void);
    NodePtr getNext(NodePtr current) const {return current->next;};
    NodePtr getHead(void) const {return head;};
    
    // Union two lists using operator overloading: + .
    // Example List1 = {1, 5, 3, 4}, List2={4, 6, 1}
    // Lu = List1 +  List2 = {1, 5, 3, 4, 6}
    List operator+(const List& l) { 

        /* union list */
        List list_union;
        
        /* First, copy current list into union list */
        NodePtr current = this->getHead();
        while (current != NULL) {
            list_union.addValue(current->value);
            current = getNext(current); 
        }
        /* Now, add any value that is not in current list to the union list */
        current = l.getHead();
        while (current != NULL) {
            if (!this->hasValue(current->value)) {
                list_union.addValue(current->value);
            }
            current = l.getNext(current); 
        }
        return list_union; 
    }
    
    /* Subtract lists (like set operations). Returns the elements that are only in current list. */
    /* Go through nodes in list1, exclude any value that is in list2. Return the remaining values */
    // Subtract two lists using operator overloading: - .
    // Example List1 = {1, 5, 3, 4}, List2={4, 6, 1}
    // Lu = List1 -  List2 = {5, 3}
    List operator-(const List& l) { 
        
        List list_sub; 
        NodePtr current = this->getHead();
        while (current != NULL) {
            list_sub.addValue(current->value);
            current = getNext(current); 
        }
        current = l.getHead();
        while (current != NULL) 
        {
            if (this->hasValue(current->value)) {
                list_sub.delValue(current->value);
            }
            current = l.getNext(current); 
        } /* while */
        return list_sub;
    }
};

/* Constructor */
List::List()
{
    /* Pointer to root of the list */
    head = NULL; 
}

/* Destructor */
List::~List() 
{
    NodePtr current = this->head;
    while (current != NULL) 
    {
        NodePtr temp = current->next; 
        delete current; 
        current = temp; 
    } 
}

/* Add a value to the list */
void List::addValue(int value)
{
    NodePtr new_node = new Node;
    new_node->next = NULL;
    new_node->value = value; 

/* Go through all nodes, reach the last node, add the value to the list*/
    if (head != NULL) { 
        NodePtr current = head;
        while (current->next != NULL){
        
            current = current->next;
        }
        current->next = new_node;
    } else { /* first node added to the list */
        head = new_node;
    }
}

/* Delete a given value from the list */
void List::delValue(int value) 
{
    NodePtr current = head; 
    NodePtr temp = head; 
    while (current != NULL && current->value != value) 
    {
        temp = current; 
        current = current->next; 
    }
    
    if (current == NULL) 
    {
        std::cout << "Error deleting given value. Could not find " << value << " in the list.\n";
    } else {
        NodePtr delValuePtr = current;
        current = current->next; 
        temp->next = current;
        if (delValuePtr == head) 
        {
            head = head->next;
            temp = NULL;
        }
        delete delValuePtr;
    }
}

/* Check if a value exists in the list */
bool List::hasValue(int value)
{
    NodePtr current = head; 
    while (current != NULL && current->value != value) 
    {
        current = current->next; 
    }
    if (current == NULL) {
        return false; 
    }
    return true;
}

/* Print the entire list */
void List::printList(void)
{
    NodePtr current = head;
    while (current != NULL){
        
        std::cout << current->value << " " << std::endl;
        current = current->next;
    }
}

/* Return the size of list */
int List::getSize(void)
{
    NodePtr current = head;
    int size = 0;
    while (current != NULL){
        size++; 
        current = current->next;
    }
    return size;
}

/****************************************************************************************/
/* main() */
/****************************************************************************************/
int main(int argc, char *argv[]) 
{
    List m; 
    m.addValue(1); 
    m.addValue(4); 
    m.addValue(6); 
    m.addValue(8); 
    std::cout << "list 1" << std::endl; 
    m.printList();
    
    List n; 
    n.addValue(1); 
    n.addValue(5); 
    n.addValue(3); 
    std::cout << "list 2" << std::endl; 
    n.printList(); 
        
    List t = m+n;
    std::cout << "Union list: list1 + list2:" << std::endl; 
    t.printList();
    std::cout << "Size: " << t.getSize() << std::endl;

    List sub = m-n;
    std::cout << "Subtract list: list1 - list2" << std::endl; 
    sub.printList();
    std::cout << "Size: " << sub.getSize() << std::endl;

    return 0;
}