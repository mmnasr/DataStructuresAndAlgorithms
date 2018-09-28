#include <iostream>
#include <queue>

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

class BTree {
private:
    struct Node {
        int data;
        struct Node* left;
        struct Node* right;
    };
    struct Node* root;
    void insertPrivate(int key, struct Node* node);
    struct Node* createNodePrivate(int key);
    int heightPrivate(struct Node* node);
    int diameterPrivate(struct Node* node, int* height);
    
public:
    BTree();
    ~BTree();
    bool isEmpty(void);
    void insert(int key);
    void printLevel(int level);
    int sumLevel(int level);
    int height(void);
    int diameter(void);
};

BTree::BTree() {
    this->root = NULL;
}

BTree::~BTree() {
    
}

void BTree::insert(int key) {
    if (this->isEmpty()) {
        this->root = this->createNodePrivate(key);
        return;   
    }
    this->insertPrivate(key, this->root);
}

/* Private functions */
void BTree::insertPrivate(int key, struct Node* node) {
    if (node == NULL) return;
    if (key < node->data) {
        if (node->left == NULL) {
            node->left = this->createNodePrivate(key);
        } else {
            this->insertPrivate(key, node->left);
        }
    } else if (key > node->data) {
        if (node->right == NULL) {
            node->right = this->createNodePrivate(key);
        } else {
            this->insertPrivate(key, node->right);
        }
    } else {
        std::cout << "Error. Key '" << key << "' already exists in the tree." << std::endl;
        return;
    }
}

void BTree::printLevel(int level) {
/* print vallues at a given level using queues */
    if (this->isEmpty()) {
        std::cout << "Empty tree. No level can be printed" << std::endl;
        return;
    }
    std::queue<struct Node* > visitedNodes;
    std::queue<int> nodeLevel;

    visitedNodes.push(this->root);
    int lev = 0;
    nodeLevel.push(lev);
    
    while ( (!visitedNodes.empty()) && (lev <= level) ){
        Node* node = visitedNodes.front();
        lev = nodeLevel.front();
        visitedNodes.pop();
        nodeLevel.pop();
        if (lev == level) {
            std::cout << node->data << " ";
            continue;
        }
        if (node->left != NULL) {
            visitedNodes.push(node->left);
            nodeLevel.push(lev+1);
        }
        if (node->right != NULL) {
            visitedNodes.push(node->right);
            nodeLevel.push(lev+1);
        }
    } /* while */
}

int BTree::sumLevel(int level) {
    if (this->isEmpty()) {
        std::cout << "Empty tree. Cannot sum at given level." << std::endl;
        return -1;
    }
    if (level == 0) return this->root->data;
    
    std::queue<struct Node* > visitedNodes;
    std::queue<int> nodeLevel;
    visitedNodes.push(this->root);
    int lev = 0;
    nodeLevel.push(lev); 
    int sum = 0;
    bool levelOutOfTreeHeight = true;
    while ( (!visitedNodes.empty()) && (lev <= level) ) {
        struct Node* node = visitedNodes.front();
        lev = nodeLevel.front();
        nodeLevel.pop();
        visitedNodes.pop();
        if (lev == level) {
            sum += node->data;
            levelOutOfTreeHeight = false;
            continue;
        }
        if (node->left != NULL) {
            visitedNodes.push(node->left); 
            nodeLevel.push(lev+1);
        }
        if (node->right != NULL) {
            visitedNodes.push(node->right);
            nodeLevel.push(lev+1);
        }
    }
    if (levelOutOfTreeHeight) {
        std::cout << "Level out of tree height: " << level << std::endl;
        return -1;
    }
    return sum;
}

/* UTILITY functions */
bool BTree::isEmpty(void) {
    return (this->root == NULL);
}

BTree::Node* BTree::createNodePrivate(int key) {
    Node* new_node = new Node;
    new_node->data = key;
    new_node->left = NULL;
    new_node->right = NULL;
    
    return new_node;
}

int BTree::height(void) {
    return this->heightPrivate(this->root);
}

int BTree::heightPrivate(struct Node* node) {
    if (node == NULL) return 0;
    return 1 + max(this->heightPrivate(node->left), this->heightPrivate(node->right));
}

int BTree::diameter(void) {

    if (this->isEmpty()) {
        std::cout << "Empty tree. Diameter zero." << std::endl;
        return 0;
    }
    int height = 0;
    return this->diameterPrivate(this->root, &height);
    
}

int BTree::diameterPrivate(struct Node* node, int* height) {

    int left_height = 0;
    int right_height = 0;
    
    int left_diameter = 0;
    int right_diameter = 0;
    
    if (node == NULL) {
        *height = 0;
        return 0; /* diameter is 0 */
    }
    
    left_diameter = this->diameterPrivate(node->left, &left_height);
    right_diameter = this->diameterPrivate(node->right, &right_height);
    
    *height = 1+ max(left_height, right_height);

    return max(left_height+right_height+1, max(left_diameter, right_diameter));
}


int main(int argc, char* argv[]) {
    BTree t;
    std::cout << "Height: " << t.height() << std::endl;    
    t.insert(5);
    t.insert(2);
    t.insert(8);
    std::cout << "Diameter: " << t.diameter() << std::endl;
    t.insert(10);
    t.insert(3);
    t.insert(9);
    std::cout << "Height: " << t.height() << std::endl;
    std::cout << std::endl;    
    int level = 5;
    t.printLevel(level);
    std::cout << "\nSum at level "<< level << " is: " << t.sumLevel(level) << std::endl;
    return 0;
}









