#include <iostream>
#include <queue>
#include <vector>

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
    void preOrderPrivate(Node* node, std::vector<int>* preOrder);
    void inOrderPrivate(Node* node, std::vector<int>* inOrder);
    bool isSubsetPrivate(std::vector<int> org, std::vector<int> sub);
    
public:
    BTree();
    ~BTree();
    bool isEmpty(void);
    void insert(int key);
    void printLevel(int level);
    int sumLevel(int level);
    int height(void);
    int diameter(void);
    bool isSubtree(class BTree sub);
    std::vector<int> inOrder(void);
    std::vector<int> preOrder(void);
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

bool BTree::isSubtree(class BTree sub) {
    std::vector<int> this_preorder = this->preOrder();
    std::vector<int> this_inorder = this->inOrder();

    std::vector<int> sub_preorder = sub.preOrder();
    std::vector<int> sub_inorder = sub.inOrder();

    if (this->isSubsetPrivate(this_preorder, sub_preorder) && 
        this->isSubsetPrivate(this_inorder, sub_inorder) ) {
        return true;
    }
    return false;
}

std::vector<int> BTree::preOrder(void) {
    std::vector<int> preOrder;
    this->preOrderPrivate(this->root, &preOrder);
    return preOrder;
}

void BTree::preOrderPrivate(Node* node, std::vector<int>* preOrder) {
    if (node == NULL) return;
    this->preOrderPrivate(node->left, preOrder);
    this->preOrderPrivate(node->right, preOrder);
    preOrder->push_back(node->data);
}

std::vector<int> BTree::inOrder(void) {
    std::vector<int> inOrder;
    this->inOrderPrivate(this->root, &inOrder);
    return inOrder;
}

void BTree::inOrderPrivate(Node* node, std::vector<int>* inOrder) {
    if (node == NULL) return;
    this->inOrderPrivate(node->left, inOrder);
    inOrder->push_back(node->data);
    this->inOrderPrivate(node->right, inOrder);
}

bool BTree::isSubsetPrivate(std::vector<int> org, std::vector<int> sub) {
    /* check if vector sub is a subset of org vector */
    if (org.size() < sub.size()) return false;
    if ( (org.size() ==0) || (sub.size() == 0)) return false;
    std::vector<int>::iterator ptr_org, ptr_sub; 
      
    for (ptr_sub = sub.begin(); ptr_sub < sub.end(); ptr_sub++) {
        for (ptr_org = org.begin(); ptr_org < org.end(); ptr_org++) {
            if (*ptr_org == *ptr_sub) break;
        }
        if (ptr_org == org.end()) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    BTree t;
    t.insert(5);
    t.insert(2);
    t.insert(8);
    t.insert(12);
    t.insert(0);
    t.insert(7);
    
    BTree ts;
    ts.insert(12);
    ts.insert(0);
    ts.insert(7);
    std::cout << "Is subtree:? " << t.isSubtree(ts) << std::endl;
    return 0;
}






