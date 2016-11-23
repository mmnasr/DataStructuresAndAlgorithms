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
    void addValue(std::string key, T value);
    void printTable(void); 
};

/* Constructor. Set TABLE_SIZE */
template <class T>
HashTable<T>::HashTable()
{
    TABLE_SIZE = 101;
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
    HashTableArray = new NodePtr[TABLE_SIZE];
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
/* There are many functions that can do this operation, but this one seems to be very */
/* at picking equally distributed values efficient */
template <class T>
unsigned int HashTable<T>::hashIndex(std::string key)
{   

    unsigned int idx;
    int which_hash = 2; 
    // https://en.wikipedia.org/wiki/Linear_congruential_generator 
    if (which_hash == 0) {
        idx = 33;
        for(unsigned int i = 0; i < key.size(); ++i)
        {
        // % 4294967296 not necessary, but there for the example.
            idx = (1013904223 + idx*1664525) % 4294967296;
        }
    } else if (which_hash == 1) {
    
        idx = 0;
        for(unsigned int i = 0; i < key.size(); ++i)
        {
            idx += (unsigned int)key[i];
        }
    } else {
        idx = 0; 
        for(unsigned int i = 0; i < key.size(); ++i)
        {
            idx += idx * 65599 + (unsigned int)key[i];
        }
    }
    return idx % TABLE_SIZE;
}

template <class T>
void HashTable<T>::addValue(std::string key, T value)
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
        while (ptr != NULL && ptr->key != key)
        {   
            ptr = ptr->next; 
        }
        /* add new node */
        if (ptr == NULL) {
            ptr = new_n;
        /* if 'key' already exists, replace the old value with new value. */
        } else {
            ptr->value = value;
        }
    }
}

template <class T>
void HashTable<T>::printTable(void)
{
    std::cout << "printing hash table...\n";
    for(int i=0; i<TABLE_SIZE; i++) 
    {
        if (HashTableArray[i] != NULL)
        {
            NodePtr ptr = HashTableArray[i];
            std::cout << "Table idx: "<< i << std::endl; 
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
    t.addValue("test", 1);
    t.addValue("test", 2);
    t.addValue("yoyo", 2);
    t.addValue("yoyo", 5);
    t.addValue("test1", 2);
    t.printTable(); 
    return 0;
}