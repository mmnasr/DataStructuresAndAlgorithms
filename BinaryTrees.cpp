/* Binary Trees: https://en.wikipedia.org/wiki/Binary_tree */
/* A C++ implementation of binary trees */
/* By: Mohamad Nasr-Azadani, mmnasr@gmail.com */
/***************************************************************************************/
/***************************************************************************************/

#include <iostream> 
#include <iomanip>
#include <deque>

template <class T> 
class BTree {
    private:
        struct Node {
            T key; 
            Node *left;  /* pointer to the left node (lesser value) */
            Node *right; /* pointer to  the right node (greater value) */
        };
        Node *root; /* pointer to the root */
    
        void deleteTreePrivate(Node* ptr);
        Node* createLeafPrivate(T key);
        T getRootKeyPrivate(void); 
        void addLeafPrivate(T key, Node* ptr); 
        void printInOrderPrivate(Node* ptr); 
        Node* getParentNodePrivate(T key, Node* parent); 
        unsigned int getChildrenCountPrivate(Node* ptr); 
        void removeKeyPrivate(T key, Node* ptr);
        void removeLeafPrivate(Node* leaf, Node* parent); 
        Node* getSmallestNodeInSubbranchPrivate(Node *current); 
        void printTreePrivate(Node* ptr, unsigned int indent); 
        
    public: 
        BTree(); 
        ~BTree();
        void addLeaf(T key);
        void printInOrder(void); 
        void printMin(void); 
        void printMax(void); 
        void printChildren(T key); 
        Node* getNode(T key); 
        Node* getParentNode(T key); 
        void removeKey(T key); 
        void printNodeAndParent(T key); 
        Node* getNodePrivate(T key, Node* ptr);
        void printInLevel(void);
        void printTree(void); 
        
        
};


/* Constructor. Set root pointer to NULL. Tree is empty. */
template <class T>
BTree<T>::BTree()
{
    root = NULL; 
}

/* Destructor. */
template <class T>
BTree<T>::~BTree()
{
    deleteTreePrivate(root); 
}

/* Delete the entire tree recursively. This  */
template<class T>
void BTree<T>::deleteTreePrivate(Node* ptr)
{
  if (ptr == NULL) return;
  deleteTreePrivate(ptr->left);
  deleteTreePrivate(ptr->right);
  delete ptr;
  ptr = NULL;
}

/* Create a new leaf (node without any children) */
template <class T>
typename BTree<T>::Node* BTree<T>::createLeafPrivate(T key)
{
    Node* new_node = new Node; 
    new_node->key = key; 
    new_node->right = NULL; 
    new_node->left = NULL; 
    
    return new_node; 
}

/* Add a leaf to the tree at the correct location */
template <class T>
void BTree<T>::addLeaf(T key)
{
    addLeafPrivate(key, root);
}

/* Add a leaf to the tree using recursion */
template <class T>
void BTree<T>::addLeafPrivate(T key, Node* ptr)
{
    if (root == NULL) 
    {
        root = createLeafPrivate(key);

    } else if (key < ptr->key) { /* go to left */
        if (ptr->left != NULL) { /* call function recursively until it can add a leaf */
            addLeafPrivate(key, ptr->left);  
        } 
        else {
            ptr->left = createLeafPrivate(key); 
        }
    } else if (key > ptr->key) { /* go to right */
        if (ptr->right != NULL) 
        {
            addLeafPrivate(key, ptr->right); 
        } 
        else {
            ptr->right = createLeafPrivate(key); 
        }
    } else {
        std::cout << "Tree already has the given key value: " << key << std::endl;
    }
}

/* Print maximum value in the tree */
template <class T>
void BTree<T>::printMax(void) 
{
    if (root == NULL) {
        std::cout << "Tree is empty. No maximum value found." << std::endl;        
    } else {
        Node* ptr = root; 
        while (ptr->right != NULL) {
            ptr = ptr->right; 
        }
        std::cout << "Maximum value in the tree is: " << ptr->key << std::endl;
    }
}

/* Print minimum value in the tree */
template <class T>
void BTree<T>::printMin(void)
{
    if (root == NULL) {
        std::cout << "Tree is empty. No minimum value found." << std::endl;
    } 
    else {
        Node* ptr = root; 
        while (ptr->left != NULL) 
        {
            ptr = ptr->left; 
        }
        std::cout << "Minimum value in the tree is: " << ptr->key << std::endl;
    }
}

/* Print the values in tree from the lowest to highest values. */
template <class T>
void BTree<T>::printInOrder(void) 
{
    printInOrderPrivate(root); 
}

/* Print the values in the tree from the lowest to the highest values recursively. */
template <class T>
void BTree<T>::printInOrderPrivate(Node* ptr)
{
    if (root != NULL) 
    {
        if (ptr->left != NULL) 
        {
            printInOrderPrivate(ptr->left);
        } 
        std::cout << ptr->key << ",";
        if (ptr->right != NULL) 
        {
            printInOrderPrivate(ptr->right); 
        }
    }
    else {
        std::cout << "The tree is empty. Cannot print the values in order." << std::endl; 
    }
}

/* Return pointer to the node with a given value */
template <class T>
typename BTree<T>::Node* BTree<T>::getNode(T key)
{
    return getNodePrivate(key, root);    
}

/* Return pointer to the node with a given value */
template <class T>
typename BTree<T>::Node* BTree<T>::getNodePrivate(T key, Node* ptr) 
{
    if (ptr == NULL) 
    {
        return NULL; 
    } 
    else {
        if (ptr->key == key) 
        {  
            return ptr;
        } else {
            if (key < ptr->key) {
                return getNodePrivate(key, ptr->left); 
            } 
            else {
                return getNodePrivate(key, ptr->right); 
            }
        }
    }
}

/* Return pointer to the parent node of a given value */
template <class T>
typename BTree<T>::Node* BTree<T>::getParentNode(T key)
{
    
    return getParentNodePrivate(key, root); 
}

/* Return pointer to the parent node of a given value */
template <class T>
typename BTree<T>::Node* BTree<T>::getParentNodePrivate(T key, Node* parent)
{
    if (parent == NULL) return NULL; 
    if ( (parent == root) && (parent->key == key)) return NULL;
    if ( (parent->left == NULL) && (parent->right == NULL) ) return NULL; 
    if ( (parent->left != NULL) && (parent->left->key == key) ) return parent; 
    if ( (parent->right != NULL) && (parent->right->key == key) ) return parent; 
    if ( (parent->left != NULL) && (parent->key > key)) 
    {
        return getParentNodePrivate(key, parent->left); 
    }    
    if ( (parent->right != NULL) && (parent->key < key) ) 
    {
        return getParentNodePrivate(key, parent->right); 
    }
}

/* Get key value of the root */
template <class T>
T BTree<T>::getRootKeyPrivate(void)
{
    if (root != NULL) 
    {
        return root->key; 
    } else {
        std::cout << "Tree is empty. Root does not have a value." << std::endl;
    }
}

/* Print children of a node with a given key value */
template <class T>
void BTree<T>::printChildren(T key) 
{
    Node* ptr = getNode(key); 
    if (ptr != NULL) 
    {
        std::cout << "Parent node: key: " << key << std::endl;
        std::cout << "Parent node has " << getChildrenCountPrivate(ptr) << " children." << std::endl; 
        if (ptr->left != NULL) 
        {
            std::cout << "   Left child: Key: " << ptr->left->key << std::endl; 
        } else {
            std::cout << "   Left child: NULL " << std::endl; 
        }
        if (ptr->right != NULL) 
        {
            std::cout << "   Right child: Key: " << ptr->right->key << std::endl;
        } else {
            std::cout << "   Right child: NULL " << std::endl; 
        }
    }
    else {
        std::cout << "The key " << key << " is not in the tree." << std::endl;
    }
}

/* Get number of children of a node. 0, 1 or 2 */
template <class T>
unsigned int BTree<T>::getChildrenCountPrivate(Node* ptr)
{
    unsigned int count = 0; 
    if (ptr->left != NULL) count++; 
    if (ptr->right != NULL) count++; 
    
    return count; 
}

/* Remove a node with a given key value from the tree */
template <class T> 
void BTree<T>::removeKey(T key)
{
    removeKeyPrivate(key, root); 
}

/* Remove a node with a given key value from the tree */
template <class T>
void BTree<T>::removeKeyPrivate(T key, Node* ptr)
{
    if (root == NULL) 
    {
        std::cout << "Tree is empty. Cannot delete the given key value." << std::endl;
    }
    else {
        /* Special case: root should be removed */
        if (root->key == key) {
            Node* current = root; 
            bool isLeaf = (current->left == NULL && current->right == NULL);
            if (isLeaf) {
                delete root; 
                root = NULL; 
                return; 
            } /* case 1: root does not have any child. */
            bool hasOnlyOneChild = (current->left == NULL && current->right != NULL) || (current->left != NULL && current->right == NULL);
            if (hasOnlyOneChild)
            {
                Node* delPtr = current; 
                if (current->left != NULL) 
                {
                    current->key = current->left->key;
                    current = current->left; 
                } else {
                    current->key = current->right->key;
                    current = current->right; 
                }
                delPtr->left = NULL;
                delPtr->right = NULL;
                delete delPtr; 
                delPtr = NULL;
                return;
            } /* case 2: Only one child */
            bool hasTwoChildren = true;
            if (hasTwoChildren) {
                Node* smallestKeyNode = getSmallestNodeInSubbranchPrivate(current->right);
                Node* parentsmallestKeyNode = getParentNode(smallestKeyNode->key); 
                std::cout << parentsmallestKeyNode->key << std::endl;

                current->key = smallestKeyNode->key;
                removeLeafPrivate(smallestKeyNode, parentsmallestKeyNode);
                return;
            }
        } /* root remove */
        Node* current = getNode(key); 
        Node* parent = getParentNode(key); 
        if (current == NULL) 
        {
            std::cout << "Cannot delete " << key << " . Value does not exist in the tree.\n" << std::endl;
            return;
        } 
        else {
            /* case 1: current key is a leaf and does not have any children */
            bool isLeaf = (current->left == NULL && current->right == NULL);
            /* A leaf node. Just delete the node from the tree */
            bool isCurrentNodeALeftChild = false; 
            if (parent->left == current) {
                isCurrentNodeALeftChild = true;
            }
            if (isLeaf) {
                removeLeafPrivate(current, parent); 
                return;
            } /* case 1: Leaf node */

            /* case 2: current key has only one child. Remove the node and connect current node's child to current node's parent */
            bool hasOnlyOneChild = (current->left == NULL && current->right != NULL) || (current->left != NULL && current->right == NULL);
            if (hasOnlyOneChild)
            {
                if (isCurrentNodeALeftChild) {
                    if (current->left != NULL) 
                    {
                        parent->left = current->left; 
                    } else {
                        parent->left = current->right; 
                    }
                } else {
                    if (current->left != NULL) 
                    {
                        parent->right = current->left; 
                    } else {
                        parent->right = current->right; 
                    }
                }
                delete current; 
                current = NULL;
                return;
            } /* case 2: Only one child */
            
            bool hasTwoChildren = true;
            if (hasTwoChildren) {
            
                Node* smallestKeyNode = getSmallestNodeInSubbranchPrivate(current->right);
                Node* parentsmallestKeyNode = getParentNode(smallestKeyNode->key); 

                current->key = smallestKeyNode->key;
                removeLeafPrivate(smallestKeyNode, parentsmallestKeyNode);
                return;
            } /* two children */
        }
    }
}

/* Find smallest value in a branch derived from a given node */
template <class T> 
typename BTree<T>::Node* BTree<T>::getSmallestNodeInSubbranchPrivate(Node* current) 
{
    if (current == NULL) {
        std::cout << "Error. Cannot find the smallest value in sub-branch for a NULL node." << std::endl;
        return NULL;
    } 
    if (current->left == NULL) {
        return current; 
    } else {
        return getSmallestNodeInSubbranchPrivate(current->left);
    }
}

/* Remove a leaf node from tree */
template <class T>
void BTree<T>::removeLeafPrivate(Node* leaf, Node* parent)
{
    Node* temp = leaf; 
    delete leaf; 
    leaf = NULL;
    if (parent->left == temp) {
        parent->left = NULL; 
    } else {
        parent->right = NULL; 
    }
    temp = NULL;
}

/* Print a node and its parent values */
template <class T>
void BTree<T>::printNodeAndParent(T key)
{
    Node *node = getNode(key); 
    Node *parent = getParentNode(key); 
    
    if (node != NULL) 
    {
        std::cout << "Node: with value: " << key << std::endl; 
    } else {
        std::cout << "No node found." << std::endl; 
    }
    if (parent != NULL) 
    {
        std::cout << "Parent found. key value:" << parent->key << std::endl;
    } else {
        std::cout << "No Parent found." << std::endl;
    }
}

/* Print the tree leve by level using Breadth-Search algorithm */
template <class T>
void BTree<T>::printInLevel(void) 
{
    if (root == NULL) 
    {
        std::cout << "Tree is empty. Cannot print values in levels." << std::endl;
        return; 
    }

    std::cout << "Printing tree by level...." << std::endl;
    std::deque<Node*> queue;
    std::deque<size_t> level;

    queue.push_back(root);
    size_t lev = 0;
    level.push_back(lev); 
    while (!queue.empty()) 
    {
        /* dequeue a node from queue */
        Node* start = queue.front();
        queue.pop_front(); 
        lev = level.front();
        level.pop_front();
        std::cout << "Level:" << lev << " " << start->key << std::endl;
        if ( (start->left != NULL) || (start->right != NULL) )
        {
            lev++; 
        }
        if (start->left != NULL) 
        { 
            queue.push_back(start->left); 
            level.push_back(lev); 
        }
        if (start->right != NULL) {
            queue.push_back(start->right); 
            level.push_back(lev); 
        }
    }
}

template <class T>
void BTree<T>::printTree(void)
{
    unsigned int indent = 0;
    printTreePrivate(root, indent); 
}

template <class T>
void BTree<T>::printTreePrivate(Node* ptr, unsigned int indent)
{
    if (ptr != NULL) 
    {
        unsigned int offset = 7;
        if (ptr->right != NULL) printTreePrivate(ptr->right, indent+offset); 
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (ptr->right != NULL) std::cout<<" /\n" << std::setw(indent) << ' '; 
        std::cout<< ptr->key << "\n ";
        if(ptr->left != NULL) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            printTreePrivate(ptr->left, indent+offset);
        }
    } 
}

/* Let's test our implementation */
int main(int argc, char *argv[]) 
{
    int tree_vals[] = {5, 7, 1, 0, 9, 3, 2, 8, 6, 4};
    BTree<int> tr; 
    tr.printInOrder(); 

    for (int i=0; i<10; ++i) {
        std::cout << tree_vals[i] << std::endl;
        tr.addLeaf(tree_vals[i]); 
    }
    tr.printMin(); 
    tr.printMax(); 
    
    tr.printInOrder(); 
    std::cout << std::endl;
    tr.printInLevel(); 
    tr.printChildren(8); 
    tr.printNodeAndParent(0);
    tr.printNodeAndParent(5);
    tr.printNodeAndParent(1);
    tr.printNodeAndParent(11);
    tr.printInOrder(); 
    std::cout << std::endl;
//    tr.removeKey(5); 
    tr.printInOrder(); 
    std::cout << std::endl;
//    tr.removeKey(0); 
    tr.printInOrder(); 
    std::cout << std::endl;
    tr.printInLevel(); 
    tr.printTree();

    return 0; 
}