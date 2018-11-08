#include <iostream> 


class Tree {
private: 
    struct Node {
        int data; 
        struct Node* left;
        struct Node* right;
    };
    struct Node* root;
    struct Node* createNodePrivate(int key) {
        struct Node* newNode = new Node;
        newNode->left = NULL;
        newNode->right = NULL;
        newnode->data = key;
        return newNode;
    }
public:
    Tree() { this->root = NULL; }
    ~Tree();
    void addKey(int key);
    bool isEmpty(void) { return this->root == NULL); }
};

Tree::~Tree() {

}

void addkey(int key) {
    if (this->isEmpty()) {
        this->root = this->createNodePrivate(key);
        return;
    }
    this->addKeyPrivate(this->root, key);
}

void Tree::addKeyPrivte(Node* node, int key) {
    if (node == NULL) return;
    if (node->left == NULL) {
        
    } else
    this->addKeyPrivate(
    if (node->right) {
    }
}

int main(int argc, char* argv[]) {

    
    return 0;
}