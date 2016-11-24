/* Hash Tables: https://en.wikipedia.org/wiki/Hash_table */
/* A C++ implementation of hash tables with pointers. */
/* By: Mohamad Nasr-Azadani, mmnasr@gmail.com */
/* Collision resolution (see https://en.wikipedia.org/wiki/Hash_table#Collision_resolution):*/
/* Separate chaining */
/***************************************************************************************/
/***************************************************************************************/

#include <cstdlib>
#include <iostream>

template <class T>
class HashTable {
private: 
    struct Node {
        T value; 
        std::string key; 
        Node *next;  
    };
    typedef struct Node* NodePtr;
    
    unsigned int TABLE_SIZE; 
    NodePtr *HashTableArray;
    
public:
    HashTable();
    ~HashTable();
    unsigned int hashIndex(std::string key);
    std::string getKey(T value);
    T getValue(std::string key);
    void putValue(std::string key, T value);
    void delValue(std::string key);
    void printValue(std::string key);
    void printTable(void); 
};

/* Constructor. Set TABLE_SIZE */
template <class T>
HashTable<T>::HashTable()
{
    /* Size of the TABLE (BUCKET Length). */
    /* Important note: The load factor defined as the (number of items) / (number of buckets) */
    /* should be small, e.g. < 10. If this number becomes very large, it would be useful to */
    /* to increase TABLE_SIZE and re-arrange the hash table again. */
    TABLE_SIZE = 2;
    
    /* Allocate memory for pointers in the HashTableArray */
    HashTableArray = new NodePtr[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        HashTableArray[i] = NULL;
    }
}

/* Destructor. Release allocated memory for hash table */
template <class T>
HashTable<T>::~HashTable()
{
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        NodePtr ptr = HashTableArray[i];
        while (ptr != NULL) {
            NodePtr temp = ptr->next; 
            delete ptr;
            ptr = temp; 
        }
    }
    delete []HashTableArray;
}

/* Converts a string to an index between 0 and TABLE_SIZE */
/* There are many functions that can do this operation. It is important to */
/* have almost a uniform and a random distribution of keys in the hash table. */
template <class T>
unsigned int HashTable<T>::hashIndex(std::string key)
{   

    unsigned int idx = 0;
//    for(unsigned int i = 0; i < key.size(); ++i)
//    {
//        idx += (unsigned int)key[i];
//    }
    for(unsigned int i = 0; i < key.size(); ++i)
    {
        idx += idx * 65599 + (unsigned int)key[i];
    }
    return idx % TABLE_SIZE;
}

/* Put a value corresponding to given key into table or the linked lists */
/* Note: If key already exists, the old value will be over-written by the new value */
template <class T>
void HashTable<T>::putValue(std::string key, T value)
{
    /* get table index corresponding to current key value */
    unsigned int idx = hashIndex(key); 
    /* if it is a new location in the table, add it */
    if (HashTableArray[idx] == NULL) 
    {
        NodePtr new_n = new Node; 
        new_n->key = key; 
        new_n->value = value; 
        new_n->next = NULL; 
        HashTableArray[idx] = new_n; 
    }   
    else { /* add the new node */
        NodePtr ptr = HashTableArray[idx];
        NodePtr new_n = new Node; 
        new_n->key = key; 
        new_n->value = value; 
        new_n->next = NULL; 
        while (ptr->next != NULL && ptr->key != key)
        {   
            ptr = ptr->next; 
        }
        /* If 'key' already exists, replace the old value with the new one. */
        if (ptr->key == key) {
            ptr->value = value;
        /* add new node */
        } else {
            ptr->next = new_n;
        }
    }
}

/* Return value corresponding to a given key */
template<class T>
T HashTable<T>::getValue(std::string key)
{
    unsigned int idx = hashIndex(key); 
    NodePtr ptr = HashTableArray[idx];
    while (ptr != NULL && ptr->key != key) 
    {
        ptr = ptr->next; 
    }
    if (ptr == NULL) {
        std::cout << "***Error. Key " << key << " does not exist.***" << std::endl;
        //throw std::invalid_argument("Key does not exist." );
        return (T)NULL;
    } else {
        return ptr->value;
    }
}

template<class T>
std::string HashTable<T>::getKey(T value)
{
    for (unsigned int i=0; i<TABLE_SIZE; ++i) 
    {
        NodePtr ptr = HashTableArray[i];
        while (ptr != NULL && ptr->value != value) 
        {
            ptr = ptr->next; 
        }/* while */
        if (ptr == NULL) {
            continue; 
        } else {
                return ptr->key; 
        } /* if-else */
    } /* for */
    std::cout << "Value " << value << " does not exist in table." << std::endl;
    return "";
}

template <class T>
void HashTable<T>::delValue(std::string key)
{
    
    unsigned int idx = hashIndex(key); 
    NodePtr ptr = HashTableArray[idx];
    if (ptr != NULL) {
        /* First item on the table is equal to key */
        if (ptr->key == key) {
            /* Case 1: Only 1 item. Item will be deleted */
            if (ptr->next == NULL) {
                HashTableArray[idx] = NULL;
                std::cout << "Key '" << key <<"' deleted." << std::endl;
                return;
            }
            /* Case 2: First item on table should be deleted, but more items are in the list corresponding to idx */
            else {
                NodePtr delNode = HashTableArray[idx]; 
                HashTableArray[idx] = HashTableArray[idx]->next;
                delete delNode;
                std::cout << "Key '" << key <<"' deleted." << std::endl;
                return;
            }
        } else {
            NodePtr p_curr = HashTableArray[idx];
            NodePtr p_next = HashTableArray[idx]->next;
            
            while (p_next != NULL && p_next->key != key)
            {
                p_curr = p_next; 
                p_next = p_next->next;
            }
            if (p_next == NULL) {
                std::cout << "Error. Table does not include key '" << key <<"'. No items deleted." << std::endl;
                return;
            } else {
                NodePtr delPtr = p_next; 
                p_next = p_next->next; 
                p_curr->next = p_next; 
                delete delPtr;
                std::cout << "Key '" << key <<"' deleted." << std::endl;
            }
        }
    } 
    else {
        std::cout << "Error. Table does not include key '" << key <<"'. No items deleted." << std::endl;
    }
}
template <class T>
void HashTable<T>::printValue(std::string key)
{
    unsigned int idx = hashIndex(key);
    NodePtr ptr = HashTableArray[idx];
    while (ptr != NULL && ptr->key != key) 
    {
        ptr = ptr->next; 
    } 
    if (ptr == NULL) {

        std::cout << "Not Found: (" << key <<","<<"None)" << std::endl;
    } else {
        std::cout << "Found: (" << key <<","<<ptr->value << ")" << std::endl;
    }
}

template <class T>
void HashTable<T>::printTable(void)
{
    std::cout << "#######################################" << std::endl;
    std::cout << "Printing hash table. Maximum (potential) table size: " << TABLE_SIZE << std::endl;
    std::cout << "#######################################" << std::endl;
    for(int i=0; i<TABLE_SIZE; i++) 
    {
        if (HashTableArray[i] != NULL)
        {
            NodePtr ptr = HashTableArray[i];
            std::cout << "Table index: "<< i << std::endl; 
            while (ptr != NULL) 
            {
                std::cout << "(" << ptr->key << "," << ptr->value << ")" << std::endl; 
                ptr = ptr->next;
            }            
            std::cout << "************************"<< std::endl; 
        }
    }
}

int main(int argc, char *argv[]) 
{
    HashTable<int> t; 
    t.putValue("foo", 1);
    t.putValue("foo", 2); /* overwrite old value equal to 1 */
    t.putValue("bar", 2);
    t.putValue("bar1", 2);
    t.putValue("foo1", -3);
    t.putValue("foo2", -4);
    t.putValue("foo3", -5);
    t.putValue("foo4", -6);
    t.putValue("foo5", -7);
    t.printTable(); 
    t.printValue("foo3"); 
    std::cout << "Value of foo1 (should be -3): " << t.getValue("foo1") << std::endl;
    std::cout << "Key for value 5 (should not exist): " << t.getKey(5) << std::endl;
    std::cout << "Deleting values from table:\n";
    t.delValue("foo3"); 
    t.delValue("foo3"); /* should not exist */
    t.delValue("foo2"); 
    t.delValue("bar"); 
    t.printTable(); 
    t.delValue("foo4"); 
    t.printTable(); 
    
    return 0;
}