#include<iostream>
using namespace std;

template<typename KEY, typename VALUE> class RBTree{
public:
	class TreeNode {
	public:
		TreeNode(KEY k, VALUE v) :key(k), value(v) {}
		TreeNode(){}
		KEY key;
		VALUE value;
		string color;
		TreeNode* left;
		TreeNode* right;
		TreeNode* parent;

	};

	TreeNode * root;
	TreeNode * empty;
	
	RBTree(void) {
		empty = new TreeNode();
		empty->color = "black";
	}

	void leftRotate(TreeNode* node) {
		TreeNode* y = node->right;
		node->right = y->left;
		if (y->left != empty) {
			y->left->parent = node;
		}
		y->parent = node->parent;
		
		if (node->parent == empty) {
			root = y;
		}
		else if (node == node->parent->left) {
			node->parent->left = y;
		}
		else {
			node->parent->right = y;
		}
		y->left = node;
		node->parent = y;
	}
	
	void rightRotate(TreeNode * node) {
		TreeNode* y = node->left;
		node->left = y->right;
		if (y->right != empty) {
			y->right->parent = node;
		}
		y->parent = node->parent;

		if (node->parent == empty) {
			root = y;
		}
		else if (node == node->parent->left) {
			node->parent->left = y;
		}
		else if (node == node->parent->right) {
			node->parent->right = y;
		}
		y->right = node;
		node->parent = y;
	}

	TreeNode * getMin() {
		TreeNode* node = root;
		while (node->left) {
			node = node->left;
		}
		return node->value;
	}

	TreeNode* getMax() {
		TreeNode* node = root;
		while (node->right) {
			node = node->right;
		}
		return node->value;
	}
	
	void insert_fix_up(TreeNode* node) {
		while (node->parent->color == "red") {
			if (node->parent == node->parent->parent->left) {
				TreeNode* y = node->parent->parent->right;
				if (y->color == "red") {
					node->parent->color = "black";
					y->color = "black";
					node->parent->parent->color = "red";
					node = node->parent->parent; 
				}
				else {
					if (node == node->parent->right) {
						node = node->parent;
						leftRotate(node);
					}
					node->parent->color = "black";
					node->parent->parent->color = "red";
					rightRotate(node->parent->parent);
				}
			}
			else {
				TreeNode* y = node->parent->parent->left;
				if (y->color == "red") {
					node->parent->color = "black";
					y->color = "black";
					node->parent->parent->color = "red";
					node = node->parent->parent;
				}
				else {
					if (node == node->parent->left) {
						node = node->parent;
						rightRotate(node);
					}
					node->parent->color = "black";
					node->parent->parent->color = "red";
					leftRotate(node->parent->parent);
				}

			}

		}
		root->color = "black";

	}

	TreeNode* successor(TreeNode * x) {
		TreeNode* y = x->parent;
		if (x->right != empty) {
			return getMin(x->right);
		}

		while ((y != empty) && (x == y->right)) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	void delete_fix_up(TreeNode * node) {
		while ((node != root) && (node->color == "black")) {
			if (node == node->parent->left) {
				TreeNode* w = node->parent->right;
				if (w->color == "red") {
					w->color = "black";
					node->parent->color = "red";
					leftRotate(node->parent);
				}
				else if (w->left->color == "black" && w->right->color == "black") {
					w->color = "red";
					node = node->parent;
				}
				else if (w->right->color == "black") {

				}
				else {
					w->color = node->parent->color;
					node->parent->color = "black";
					w->left->color = "black";
					rightRotate(node->parent);
					node->root;
				}
			}
			else {
				TreeNode* w = node->parent->left;
				if (w->color == "red") {
					w->color = "black";
					node->parent->color = "red";
					rightRotate(node->parent);
				}
				else if (w->left->color == "black" && w->right->color == "black") {
					w->color = "red";
					node = node->parent;
				}
				else if (w->left->color == "black") {
					w->right->color = "black";
					w->color = "red";
					leftRotate(w);
				}
				else {
					w->color = node->parent->color;
					node->parent->color = "black";
					w->left->color = "black";
					rightRotate(node->parent);
					node = root;
				}
			}
		}
		node->color = "black";
	}

	void insert_node(KEY key, VALUE value) {


		TreeNode* ptr = root;
		TreeNode* result = empty;
		while (ptr)
		{
			result = ptr;
			if (ptr->key > key) {
				ptr = ptr->right;
			}
			else if (ptr->key < key) {
				ptr = ptr->left;
			}
			else {
				return;
			}
		}
		TreeNode* node = new TreeNode(key, value);
		node->parent = result;

		if (result == empty) {
			root = node;
		}
		else if (key < result->key) {
			result->left = node;

		}
		else if (key > result->key) {
			result->right = node;
		}
		result->left = empty;
		result->right = empty;
		node->color = "red";

	}

	TreeNode* search(KEY key) {
		TreeNode* node = root;
		while (node != empty) {
			if (key < node->key) {
				node = node->left;
			}
			else if (key > node->key) {
				node = node->right;
			}
			else return node;
		}
		return empty;
	}

	void delete_by_key(KEY * key) {
		TreeNode * z = search(key);
		if (z == empty) {
			return;
		}

		TreeNode* y = empty;
		TreeNode* x = empty;

		if (z->left == empty || z->right == empty) {
			y = z;
		}
		else {
			y = successor(key);
		}

		if (y->left != empty) {
			x = y->left;
		}
		else if (y->right != empty) {
			x = y->right;
		}

		//直接替换
		x->parent = y->parent;
		if (y->parent == empty) {
			root = x;
		}
		else if (y == y->parent->left) {
			y->parent->left = x;
		}
		else {
			y->parent->right = x;
		}

		//更换内部
		if (y != z) {
			z->key = y->key;
			z->value = y->value;
		}
		if (y->color == "black") {
			delete_fix_up(x);
		}
		return y;

	}



	

};