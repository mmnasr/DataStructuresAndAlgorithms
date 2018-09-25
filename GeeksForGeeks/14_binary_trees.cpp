#include <iostream>

class BTree{
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

public:
	BTree();
	~BTree();
	void addLeaf(int key);
	bool isLeaf(Node* node);
	bool isEmpty(void);
	void printPostOrder(void);
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
		std::cout << "Empty tree. Nothing to print (postorder)" << std::endl;
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
	std::cout << node->data << " ";//std::endl;
}

int main(int argc, char *argv[]) {
	BTree t;
	t.addLeaf(2);
	t.addLeaf(4);
	t.addLeaf(5);
	t.addLeaf(1);
	t.printPostOrder();
	return 0;
}



