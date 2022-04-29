#include "Treap.h"

//Default constructor for the treap
Treap::Treap() {
	Node* root = nullptr;
}

// delete the treap
Treap::~Treap() {

}

//deletes all nodes from treap
void Treap::clear() {
	while (!keys.empty()) {
		root = remove(root, keys.back());
		keys.pop_back();
	}
}

//searches through treap and returns node when found, if not found throw exception for now
Treap::Node* Treap::search(Node* root, int key) {
	//root doesnt exist or root is key
	if (root == nullptr || root->key == key) {
		return root;
	}
	else if (root->key < key) {
		return Treap::search(root->right, key);
	}
	else {
		return Treap::search(root->left, key);
	}
}

//searches through treap and returns parent of node when found
Treap::Node* Treap::parentSearch(Node* root, int key) {
	if (root == nullptr) {
		return root;
	}
	else if (root->key < key) {
		if (root->right->key == key) {
			return root;
		}
		else {
			return Treap::parentSearch(root->right, key);
		}
	}
	else {
		if (root->left->key == key) {
			return root;
		}
		else {
			return Treap::parentSearch(root->left, key);
		}
	}
}

//inserts new node into treap
Treap::Node* Treap::insert(Node* root, int key) {
	if (root == nullptr) {
		return newNode(key);
	}
	//if key is smaller or equal than root
	if (key <= root->key) {
		//insert in left subtree
		root->left = insert(root->left, key);

		//fix heap property if needed
		if (root->left->priority > root->priority) {
			root = rotateR(root);
		}
	}
	else {	//key is greater than root
		// Insert in right subtree
		root->right = insert(root->right, key);

		// Fix Heap property if it is violated
		if (root->right->priority > root->priority)
			root = rotateL(root);
	}
	return root;
}

//removes node with key from treap
Treap::Node* Treap::remove(Node* root, int key) {
	if (root == nullptr)
		return root;

	if (key < root->key)
		root->left = remove(root->left, key);
	else if (key > root->key)
		root->right = remove(root->right, key);

	// IF KEY IS AT ROOT

	// If left doesnt exist
	else if (root->left == nullptr)
	{
		Node* temp = root->right;
		delete(root);
		root = temp;  // Make right child as root
	}

	// If Right doesnt exist
	else if (root->right == nullptr)
	{
		Node* temp = root->left;
		delete(root);
		root = temp;  // Make left child as root
	}

	// If key is at root and both left and right exist
	else if (root->left->priority < root->right->priority)
	{
		root = rotateL(root);
		root->left = remove(root->left, key);
	}
	else
	{
		root = rotateR(root);
		root->right = remove(root->right, key);
	}

	return root;
}

//rotates the treap right at given root
Treap::Node* Treap::rotateR(Node* root) {
	Node* x = root->left;
	Node* temp = x->right;

	x->right = root;
	root->left = temp;

	return x;
}

//rotates the treap left at given root
Treap::Node* Treap::rotateL(Node* root) {
	Node* x = root->right;
	Node* temp = x->left;

	x->left = root;
	root->right = temp;

	return x;
}

//rotates the treap right, but finds the node to rotate based on key
Treap::Node* Treap::justRotateR(Node* root, int key) {
	//search
	if (key < root->key) {
		//search left
		root->left = justRotateR(root->left, key);
	}
	else if (key > root->key) {
		//search right
		root->right = justRotateR(root->right, key);
	}
	else if (key == root->key) {	//found node
		root = rotateR(root);
	}
	return root;
}

//rotates the treap left, but finds the node to rotate based on key
Treap::Node* Treap::justRotateL(Node* root, int key) {
	//search
	if (key < root->key) {
		//search left
		root->left = justRotateL(root->left, key);
	}
	else if (key > root->key) {
		//search right
		root->right = justRotateL(root->right, key);
	}
	else if (key == root->key) {	//found node
		root = rotateL(root);
	}
	return root;
}

//////////////////////////PRIVATE///////////////////////////////////////////////////

//creates a new node with given key
Treap::Node* Treap::newNode(int key) {
	keys.push_back(key);

	Node* temp = new Node;
	temp->key = key;
	temp->priority = rand() % 100;
	temp->left = temp->right = nullptr;
	return temp;
}

//prints treap to console for debugging
void Treap::inOrder(Node* root) {
	if (root != nullptr) {
		inOrder(root->left);
		std::cout << "key: " << root->key << " | priority: " << root->priority << '\n';
		if (root->left != nullptr) {
			std::cout << " | left child: " << root->left->key << '\n';
		}
		if (root->right != nullptr) {
			std::cout << " | right child: " << root->right->key << '\n';
		}
		inOrder(root->right);
	}
}