#include <bits/stdc++.h>

#define f first
#define s second
#define loop(i, n) for (int i = 0; i < n; ++i)
#define read(a, n) loop($, n) cin >> a[$];
#define show(a, n)                  \
    loop($, n) cout << a[$] << " "; \
    cout << endl;

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

/*	// RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0, 2^32 - 1]
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
*/

/* // TIME
auto start = chrono::high_resolution_clock::now();
// ...
auto stop = chrono::high_resolution_clock::now();
auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
cout << duration.count() << endl;
*/

template<class type = int>
struct tree {

	struct node {

		node *left, *right;
		type data;
		int height, size;	// of subtree

		node(type val) : left(NULL), right(NULL), data(val), height(1), size(1) {}

	};

	node *root;

	tree() : root(NULL) {}

	inline type mn(node *root){
		while (root->left) {
			root = root->left;
		}
		return root->data;
	}

	inline type mx(node *root){
		while (root->right) {
			root = root->right;
		}
		return root->data;
	}

	// Recomputes height and size of root
	inline void update(node *root){
		root->height = 1;
		root->size = 1;
		if (root->left) {
			root->height = max(root->height, root->left->height + 1);
			root->size += root->left->size;
		}
		if (root->right) {
			root->height = max(root->height, root->right->height + 1);
			root->size += root->right->size;
		}
	}

	inline node *rotate(node *root, bool right) {
		assert((right ? root->left : root->right) != NULL);
		node *new_root = (right ? root->left : root->right);
		(right ? root->left : root->right) = (right ? new_root->right : new_root->left);
		(right ? new_root->right : new_root->left) = root;
		update(right ? new_root->right : new_root->left);
		update(new_root);
		return new_root;
	}

	inline int height(node *root){
		return root ? root->height : 0;
	}

	// Performs rebalancing and updates height and size
	inline node *balance(node *root){
		int bal = height(root->left) - height(root->right);
		if (bal > 1) {
			node *child = root->left;
			if (height(child->left) < height(child->right)) {
				root->left = rotate(child, false);
			}
			return rotate(root, true);
		} else if (bal < -1) {
			node *child = root->right;
			if (height(child->right) < height(child->left)) {
				root->left = rotate(child, true);
			}
			return rotate(root, false);
		}
		update(root);
		return root;
	}

	node *find(node *root, type val) {
		if (root == NULL) {
			return NULL;
		}
		if (root->data == val) {
			return root;
		}
		if (root->data > val) {
			return find(root->left, val);
		}
		return find(root->right, val);
	}

	inline node *find(type val) {
		return find(root, val);
	}

	node *insert(node *root, type val) {
		if (root == NULL) {
			return new node(val);
		}
		if (root->data > val) {
			root->left = insert(root->left, val);
		} else if (root->data < val) {
			root->right = insert(root->right, val);
		}
		return balance(root);
	}

	inline void insert(type val) {
		root = insert(root, val);
	}

	node *erase(node *root, type val) {
		if (root == NULL) {
			return NULL;
		}
		if (root->data > val) {
			root->left = erase(root->left, val);
		} else if (root->data < val) {
			root->right = erase(root->right, val);
		} else {
			if (root->left == NULL) {
				node *temp = root->right;
				delete root;
				return temp;
			}
			if (root->right == NULL) {
				node *temp = root->left;
				delete root;
				return temp;
			}
			type pred = mx(root->left);
			root->left = erase(root->left, pred);
			root->data = pred;
		}
		return balance(root);
	}

	inline void erase(type val) {
		root = erase(root, val);
	}

	void preorder(node *root){
		if (root == NULL){
			return;
		}
		cout << root->data << " ";
		preorder(root->left);
		preorder(root->right);
	}

	inline void preorder(){
		preorder(root);
	}

	void inorder(node *root){
		if (root == NULL){
			return;
		}
		inorder(root->left);
		cout << root->data << " ";
		inorder(root->right);
	}

	inline void inorder(){
		inorder(root);
	}

	void postorder(node *root){
		if (root == NULL){
			return;
		}
		postorder(root->left);
		postorder(root->right);
		cout << root->data << " ";
	}

	inline void postorder(){
		postorder(root);
	}
};

int main() {
	/*	// IO
	ios_base::sync_with_stdio(false);	// unsync C- and C++-streams (stdio, iostream)
	cin.tie(NULL);	// untie cin from cout (no automatic flush before read)
	*/
	tree<int> tree;
	int n, m;
	cin >> n >> m;
	loop(i, n){
		int u;
		cin >> u;
		tree.insert(u);
		tree.inorder();
		cout << "Height: " << tree.root->height << endl;
	}
	cout << "Size: " << tree.root->size << endl;
	loop(i, m){
		int u;
		cin >> u;
		tree.erase(u);
		tree.inorder();
		cout << "\nSize: " << tree.root->size << "Height: " << tree.root->height << endl;
	}
	return 0;
}
