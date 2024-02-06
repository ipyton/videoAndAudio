#include<iostream>
using namespace std;

template<typename KEY, typename VALUE>
class TreeNode {
public:
	TreeNode(KEY k, VALUE v, string color) :key(k), value(v), color(color) {}
	TreeNode() {}
	KEY key;
	VALUE value;
	string color;
	TreeNode<KEY,VALUE>* left;
	TreeNode<KEY,VALUE>* right;
	TreeNode<KEY,VALUE>* parent;

};


template<typename KEY, typename VALUE> class RBTree {
public:
	TreeNode<KEY, VALUE>* root;
	TreeNode<KEY, VALUE>* empty;

	RBTree(void) {
		empty = new TreeNode<KEY, VALUE>();
		empty->color = "black";
		root = empty;
	}

	TreeNode<KEY,VALUE> * createNode(KEY key, VALUE value) {
		TreeNode<KEY,VALUE> * node = new TreeNode<KEY,VALUE> (key, value, "red");
		node->left = empty;
		node->right = empty;
		return node;
	}

	void leftRotate(TreeNode<KEY,VALUE>* node) {
		TreeNode<KEY,VALUE>* y = node->right;
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
	
	void rightRotate(TreeNode<KEY,VALUE> * node) {
		TreeNode<KEY,VALUE> * y = node->left;
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

	TreeNode<KEY,VALUE> * getMin() {
		TreeNode<KEY,VALUE>* node = root;
		while (node->left) {
			node = node->left;
		}
		return node->value;
	}

	TreeNode<KEY,VALUE> * getMax() {
		TreeNode<KEY,VALUE>* node = root;
		while (node->right) {
			node = node->right;
		}
		return node->value;
	}
	
	void insert_fix_up(TreeNode<KEY,VALUE> * node) {
		while (node->parent->color == "red") {
			if (node->parent == node->parent->parent->left) {
				TreeNode<KEY,VALUE>* y = node->parent->parent->right;
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
				TreeNode<KEY,VALUE>* y = node->parent->parent->left;
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

	TreeNode<KEY,VALUE> * successor(TreeNode<KEY,VALUE> * x) {
		TreeNode<KEY,VALUE>* y = x->parent;
		if (x->right != empty) {
			return getMin(x->right);
		}

		while ((y != empty) && (x == y->right)) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	void delete_fix_up(TreeNode<KEY,VALUE> * node) {
		while ((node != root) && (node->color == "black")) {
			if (node == node->parent->left) {
				TreeNode<KEY,VALUE>* w = node->parent->right;
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
				TreeNode<KEY, VALUE>* w = node->parent->left;
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


		TreeNode<KEY,VALUE> * ptr = root;
		TreeNode<KEY,VALUE> * result = empty;

		while (ptr != empty)
		{
			result = ptr;
			if (ptr->key > key) {
				ptr = ptr->left;
			}
			else if (ptr->key < key) {
				ptr = ptr->right;
			}
			else {
				return;
			}
		}
		TreeNode<KEY,VALUE>* node = createNode(key,value);
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
		node->color = "red";
		insert_fix_up(node);

	}

	TreeNode<KEY,VALUE> * search(KEY key) {
		TreeNode<KEY,VALUE> * node = root;
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
		TreeNode<KEY,VALUE> * z = search(key);
		if (z == empty) {
			return;
		}

		TreeNode<KEY,VALUE> * y = empty;
		TreeNode<KEY,VALUE> * x = empty;

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

	void traverse(TreeNode<KEY, VALUE> * node) {
		if (node == empty) return;
		traverse(node->left);
		cout << node->key << " " << node->value << " " << node->color << endl;
		traverse(node->right);
	}

	void traverse(void) {
		traverse(root);
	}


};