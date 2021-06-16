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

		node(type val) : left(NULL), right(NULL), data(val){}

	};

	node *root;

	tree() : root(NULL) {}

	// Returns min element in subtree rooted at root
	inline type mn(node *root){
		while (root->left) {
			root = root->left;
		}
		return root->data;
	}

	// Returns max element in subtree rooted at root
	inline type mx(node *root){
		while (root->right) {
			root = root->right;
		}
		return root->data;
	}

	// Returns node of value val in subtree rooted at root (NULL if not present)
	node *find(node *root, type val) {
		if (root == NULL) {
			return NULL;
		}
		if (val < root->data) {
			return find(root->left, val);
		}
		if (val > root->data) {
			return find(root->right, val);
		}
		return root;
	}

	inline node *find(type val) {
		return find(root, val);
	}

	// Inserts val into subtree rooted at root
	node *insert(node *root, type val) {
		if (root == NULL) {
			return new node(val);
		}
		if (val < root->data) {
			root->left = insert(root->left, val);
		} else if (val > root->data) {
			root->right = insert(root->right, val);
		}
		return root;
	}

	inline void insert(type val) {
		root = insert(root, val);
	}

	// If present, removes val from subtree rooted at root
	node *erase(node *root, type val) {
		if (root == NULL) {
			return NULL;
		}
		if (val < root->data) {
			root->left = erase(root->left, val);
		} else if (val > root->data) {
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
		return root;
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
	string line;
	tree<int> bst;
	while (cin) {
		getline(cin, line);
		if (line.substr(0, 2) == "I ") {
			bst.insert(stoi(line.substr(2)));
		} else if (line.substr(0, 2) == "P ") {
			int u = stoi(line.substr(2));
			if (bst.find(u)){
				cout << u << " existe" << endl;
			}else{
				cout << u << " nao existe" << endl;
			}
		} else if (line.substr(0, 2) == "R ") {
			bst.erase(stoi(line.substr(2)));
		} else if (line == "PREFIXA") {
			bst.preorder();
			cout << endl;
		} else if (line == "INFIXA") {
			bst.inorder();
			cout << endl;
		} else if (line == "POSFIXA") {
			bst.postorder();
			cout << endl;
		}
	}
	return 0;
}
