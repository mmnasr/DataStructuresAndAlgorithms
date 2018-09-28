#include <iostream>
#define MINUS_INF -100000000

class BTree {
private:
	struct Node {
		int data;
		struct Node* left;
		struct Node* right;
	};
	Node* root;
	Node *createLeafPrivate(int key);
	void addLeafPrivate(int key, Node* node);
	void printPostOrderPrivate(Node* node);
	void printPreOrderPrivate(Node* node);
	void printInOrderPrivate(Node* node);
	void printLevelPrivate(Node* node, int lev);
	void maxPrivate(Node* node, int* currentMax);
	void maxLevelPrivate(Node* node, int level, int* max);

public:
	BTree();
	~BTree();
	void addLeaf(int key);
	bool isLeaf(Node* node);
	bool isEmpty(void);
	void printPostOrder(void);
	void printPreOrder(void);
	void printInOrder(void);
	void printLevel(int lev);
	int max(void);
	int maxLevel(int level);
};

BTree::BTree() {
	root = NULL;
}

BTree::~BTree() {
	
}
bool BTree::isEmpty(void) {
	return (this->root == NULL);
}

bool BTree::isLeaf(Node* node) {
	if ( (node == NULL) || ( (node->left == NULL) && (node->right == NULL) ) ) return true;
	return false;
}

BTree::Node* BTree::createLeafPrivate(int key) {
	Node* new_node = new Node;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->data = key;
	return new_node;
}

void BTree::addLeafPrivate(int key, Node* node) {
	if (this->isEmpty()) {
		this->root = this->createLeafPrivate(key);
		return;
	}
	if (key < node->data) {
		if (node->left != NULL) {
			this->addLeafPrivate(key, node->left);
		} else {
			node->left = this->createLeafPrivate(key);
			return;
		}
	} else if (key > node->data) {
		if (node->right != NULL) {
			this->addLeafPrivate(key, node->right);
		} else {
			node->right = this->createLeafPrivate(key);
			return;
		}
	} else {
		std::cout << "Warning. Tree already has the key value: " << key << std::endl;
		return;
	}
}

void BTree::addLeaf(int key) {
	this->addLeafPrivate(key, this->root);
}

void BTree::printPostOrder(void) {
	if (this->isEmpty()) {
		std::cout << "Empty tree. Nothing to print (postorder)." << std::endl;
		return;
	}
	this->printPostOrderPrivate(this->root);
}

void BTree::printPostOrderPrivate(Node* node) {
	if (node == NULL) {
		return;
	}
	this->printPostOrderPrivate(node->left);
	this->printPostOrderPrivate(node->right);
	std::cout << node->data << " ";
}

void BTree::printPreOrder(void) {
	if (this->isEmpty()) {
		std::cout << "Empty tree. Nothing to print (preorder)." << std::endl;
		return;
	}
	this->printPreOrderPrivate(this->root);
}

void BTree::printPreOrderPrivate(Node* node) {
	if (node == NULL) {
		return; 
	}
	std::cout << node->data << " " ;
	this->printPreOrderPrivate(node->left);
	this->printPreOrderPrivate(node->right);
}

void BTree::printInOrder(void) {
	if (this->isEmpty()) {
		std::cout << "Empty tree. Nothing to print (Inorder)." << std::endl;
		return;
	}
	this->printInOrderPrivate(this->root);
}

void BTree::printInOrderPrivate(Node* node) {
	if (node == NULL) {
		return;
	}
	this->printInOrderPrivate(node->left);
	std::cout << node->data << " ";
	this->printInOrderPrivate(node->right);
}

void BTree::printLevel(int lev) {
	if (this->isEmpty()) {
		std::cout << "Empty tree. Nothing to print (level)." << std::endl;
		return;
	}
	std::cout << "Print level " << lev << " of the tree" << std::endl;
	this->printLevelPrivate(this->root, lev);
}

void BTree::printLevelPrivate(Node* node, int lev) {
	if (node == NULL) return;
	if (lev == 0) {
		std::cout << node->data << " ";
	} else if (lev > 0) {
		this->printLevelPrivate(node->left, lev-1);
		this->printLevelPrivate(node->right, lev-1);
	}
}

int BTree::max(void) {
	if (this->isEmpty()) {
		std::cout << "Empty tree. No max value." << std::endl;
		return -1;
	}
	int max = MINUS_INF;
	this->maxPrivate(this->root, &max);
	return max;
}

void BTree::maxPrivate(Node* node, int* currentMax) {
	if (node == NULL) {
		return;
	}
	if (node->data > *currentMax) {
		*currentMax = node->data;
	}
	this->maxPrivate(node->left, currentMax);
	this->maxPrivate(node->right, currentMax);
}

int BTree::maxLevel(int level) {
	if (this->isEmpty()) {
		std::cout << "Empty tree. No max value at any level." << std::endl;
		return -1;
	}
	int max = MINUS_INF;
	this->maxLevelPrivate(this->root, level, &max);
	return max;
}

void BTree::maxLevelPrivate(Node* node, int level, int* max) {
	if (node == NULL) return;
	if ( (level == 0) && (node->data > *max) ){
		*max = node->data;
	}
	this->maxLevelPrivate(node->left, level-1, max);
	this->maxLevelPrivate(node->right, level-1, max);
}

int main(int argc, char *argv[]) {
	BTree t;
	t.addLeaf(2);
	t.addLeaf(4);
	t.addLeaf(5);
	t.addLeaf(1);
	t.addLeaf(19);
	t.addLeaf(23);
	t.printPostOrder();
	std::cout << std::endl;
	t.printPreOrder();
	std::cout << std::endl;
	t.printInOrder();
	std::cout << std::endl;
	t.printLevel(1);
	std::cout << std::endl;
	std::cout << t.max() << std::endl;
	std::cout << t.maxLevel(1) << std::endl;
	return 0;
}



