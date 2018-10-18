#include <iostream> 
#include <stack>
#include <map>

struct Node {
    int data;
    Node* left; 
    Node* right;
};

Node* createNode(int key) {
    Node* newNode = new Node; 
    newNode->data = key;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

void printTree(Node* node) {
    if (node == NULL) return;
    std::cout << node->data << " ";
    printTree(node->left);   
    printTree(node->right);   
}

int sumAllPathsToLeaves(Node* node, int sum) {
    if (node == NULL) return 0;
    sum = sum + node->data;
    if (node->left == NULL && node->right == NULL) 
        return sum;
    return ( sumAllPathsToLeaves(node->left, sum) + sumAllPathsToLeaves(node->right, sum));
}

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
// https://www.geeksforgeeks.org/given-a-binary-tree-print-all-root-to-leaf-paths/
void printArray(int* arr, int len) {
    for (int i=0; i < len; i++) 
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}


void printAllPathsToLeavesPrivate(Node* node, int* paths, int length) {
    if (node == NULL) return;
    paths[length++] = node->data;
    if (node->left == NULL && node->right == NULL) {
        std::cout << "Path found (root to leaf):\n";
        printArray(paths, length);
    } else {
        printAllPathsToLeavesPrivate(node->left, paths, length);
        printAllPathsToLeavesPrivate(node->right, paths, length);
    }
}

void printAllPathsToLeaves(Node* node) {
    int paths[10000];
    int length = 0;
    printAllPathsToLeavesPrivate(node, paths, length);
}
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

void printRootToLeaf(Node* leaf, std::map<Node*, Node*> parent) {
    std::stack<Node*> nodeStack;
    Node* current = leaf;
    
    while (current) {
        nodeStack.push(current);
        current = parent[current];
    }
    
    while (!nodeStack.empty()) {
        current = nodeStack.top();
        std::cout << current->data << " ";
        nodeStack.pop();
    }
    std::cout << "\n";
}

void printLeafToRootNoRecursion(Node* node) {

    if (node == NULL) return;
    
    std::map<Node*, Node*> parent;
    parent[node] = NULL;
    
    std::stack<Node*> nodeStack;
    nodeStack.push(node);
    
    while (!nodeStack.empty()) {
        Node* current = nodeStack.top();
        nodeStack.pop();
        
        if (current->left == NULL && current->right == NULL) {
            printRootToLeaf(current, parent);
        }
        if (current->left) {
            parent[current->left] = current;
            nodeStack.push(current->left);
        }
        if (current->right) {
            parent[current->right] = current;
            nodeStack.push(current->right);
        }
    }
}
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/



int main(int argc, char* argv[]) {
    Node* root = createNode(1);
    
    root->left = createNode(2);
    root->right = createNode(3);

    root->left->left = createNode(0);
    //root->left->right = createNode(6);

    //root->right->left = createNode(7);
        
    printTree(root);
    std::cout << "\n";
    
    std::cout << "sum paths: " << sumAllPathsToLeaves(root, 0) << std::endl;
    printAllPathsToLeaves(root);
    std::cout << "\n";
    printLeafToRootNoRecursion(root);


    std::cout << "\n";
    return 0;
}