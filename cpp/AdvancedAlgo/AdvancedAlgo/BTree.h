#include<iostream>
using namespace std;

template<typename KEY, typename VALUE>
class BTreeNode {
public:
	bool isLeaf;
	//children的数量
	int num;
	vector<BTreeNode*> children;
	vector<KEY*> keys;


	BTreeNode(int t, int isLeaf) {

	}

	BTreeNode() {

	}

	~BTreeNode() {
		for (BTreeNode* node : children) {
			delete node;
		}
		for (KEY* key : keys) {
			delete key;
		}

	}

};

template<typename KEY, typename VALUE>
class BTree
{
public:
	BTreeNode<KEY, VALUE> * root;

	// t is a barrier for minimum requirement for composition for a node
	int t;

	BTree(int degree) t(degree){
		
	}

	BTreeNode * createBTreeNode(int l, bool leaf) {
		BTreeNode* node = new BTreeNode();
		node->isLeaf = leaf;
		node->keys = new vector<KEY>();
		node->children = new vector<BTreeNode<>>();
		node->num = 0;

		return node;
	}

	void split_child(BTreeNode* x, int numOfChild) {
		BTreeNode* y = x->children[numOfChild];
		BTreeNode* z = createBTreeNode(degree, y->leaf);
		
		z->num = t - 1;

		int j = 0;
		for (j = 0; j < t - 1; j ++) {
			z->keys[j] = y->keys[j + t];
		}

		if (!y->leaf) {
			for (j = 0; j < t; j ++) {
				z->children[j] = y->children[j + t];
			}
		}

		y->num = t - 1;
		for (j = x->num; j >= numOfChild + 1; j --) {
			x->children[j + 1] = x->children[j];
		}
		x->chihldren[numOfChild + 1] = z;

		for (j = x->num - 1; j >= numOfChild; j --) {
			x->keys[j + 1] = x->keys[j];
		}

		x->keys[numOfChild] = y->keys[t - 1];
		x->num += 1;
	}

	void insert_nonfull(BTreeNode * x, KEY key) {
		int i = x->num - 1;

		if (x->leaf) {
			while (i >= 0 && x->keys[i] > k) {
				x->keys[i + 1] = x->keys[i];
				i--;
			}
			x->keys[i + 1] = k;
			x->num += 1;
		}
		else {
			while (i >= 0 && x->keys[i] > k) i--;
			if (x->children[i + 1]->num == 2 * t - 1) {
				split_child(x, i + 1);
				if (k > x->keys[i + 1]) i ++;
			}
			insert_nonfull(x->children[i + 1], k);
		}

	}

	void insert(KEY key) {
		BTreeNode* r = root;
		if (r->num == 2 * t - 1) {
			BTreeNode* node = createBTreeNode(t, 0);
			root = node;
			node->children[0] = r;
			split_child(node, 0);

			int i = 0;
			if (node->keys[0] < key) i++;
			insert_nonfull(node->children[i], key);
		}
		else {
			insert_nonfull(r, key);
		}
	}

	void traverse(BTreeNode* node) {
		int i = 0;
		for (i = 0; i < x->num; i++) {
			if (x->leaf == 0) {
				traverse(x->children[i]);
			}
			printf("%C", x->keys[i]);
		}
		if (!x->leaf) {
			traverse(x->children[i]);
		}
	}

	void print() {

	}

	int bin_search(int low, int high, KEY key) {
		int mid;
		if (low > high || low < 0 || high < 0) {
			return -1;
		}
		while (low <= high) {
			mid = (low + high) / 2;
			if (key > node->keys[mid]) {
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
		}
		return low;
	}

	void merge(BTreeNode* node, int idx) {
		BTreeNode* left = node->children[idx];
		BTreeNode* right = node->children[idx + 1];

		int i = 0;
		left->keys[t - 1] = node->keys[idx];
		for (int i = 0; i < t - 1; i++) {
			left->keys[t + i] = right->keys[i];
		}

		if (!left->leaf) {
			for (i = 0; i < t; i++) {
				left->children[t + i] = right->children[i];
			}
		}
		left->num += t;
		delete right;

		for (i = idx + 1; i < node->num; i++) {
			node->keys[i - 1] = node->keys[i];
			node->children[i] = node->children[i + 1];
		}

		node->children[i + 1] = NULL;
		node->num -= 1;

		if (node->num == 0) {
			root = left;
			delete node; 
		}
	}

	void delete_key(BTreeNode* node, KEY key) {
		if (node == nullptr) return;

		int idx = 0, i;

		while (idx < node->num && key > node->keys[idx]) {
			idx++;
		}

		if (idx < node->num && key == node->keys[idx]) {

			if (node->leaf) {	
				for (i = idx; i < node->num - 1; i++) {
					node->keys[i] = node->keys[i + 1];
				}

				node->keys[node->num - 1] = 0;
				node->num--;

				if (node->num == 0) {
					delete node;
					// ???
					//root = NULL;
				}

				return;
			}
			else if (node->children[idx]->num >= t) {
				//the number of children larger than t
				BTreeNode* left = node->children[idx];
				node->keys[idx] = left->keys[left->num - 1];
				delete_key(left, left->keys[left->num - 1]);
			}
			else if (node->children[idx + 1]->num >= t) {
				// the number of 
				BTreeNode* right = node->children[idx + 1];
				node->keys[idx] = right->keys[0];
				delete_key(right, right->keys[0]);
			}
			else {
				merge(node, idx);
				delete_key(node->children[idx], key);
			}
		}
		else {
			//idx >= node->num || key < node->keys[idx]
			//go to find its children
			BTReeNode* child = node->children[idx];
			if (child == NULL) {
				return;
			}
			if (child->num == t - 1) {

				BTreeNode* left;
				BTreeNode* right;

				if (idx - 1 >= 0) {

				} 
				if (idx + 1 <= node->num) {

				}
				if ((left && left->num >= t) || (right && right->num >= t)) {

				}



			}
			else if ((!left || (left->num == t - 1)) && 
				(!right || (right->num ==t - 1)) {
			}


		}
	}

	int delete_node(BTreeNode* node, KEY key) {
		if (!root) return -1;
		delete_key(root, key);
		return 0;
	}

	int ~BTree() {
		delete root;
	}

};

