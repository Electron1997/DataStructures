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


/* // TIME
auto start = chrono::high_resolution_clock::now();
// ...
auto stop = chrono::high_resolution_clock::now();
auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
cout << duration.count() << endl;
*/

// rng() generates u.a.r. from [0, 2^32 - 1]
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Creates skip list with probability NUM/DEN
template<class type, type VAL_MIN = INT_MIN, type VAL_MAX = INT_MAX, int NUM = 1, int DEN = 2>
struct skiplist{

	struct node{

		node(type val) : left(NULL), right(NULL), above(NULL), below(NULL), data(val){}

		node *left, *right, *above, *below;
		type data;
	
	};

	// rng() generates u.a.r. from [0, 2^32 - 1]
	mt19937 rng;

	// length : number of elements in list (not counting sentinels), height : number of layers
	int length, height;

	node *head, *head_top, *tail, *tail_top;

	// Initialize rng, set up sentinels
	skiplist() : length(0), height(1), rng(mt19937(chrono::steady_clock::now().time_since_epoch().count())){
		head = head_top = new node(VAL_MIN);
		tail = tail_top = new node(VAL_MAX);
		head->right = tail;
		tail->left = head;
	}

	inline add_layer(){
		head_top->above = new node(VAL_MIN);
		head_top->above->below = head_top;
		head_top = head_top->above;
		tail_top->above = new node(VAL_MAX);
		tail_top->above->below = tail_top;
		tail_top = tail_top->above;
		head_top->right = tail_top;
		tail_top->left = head_top;
		++height;
	}

	// Finds first node with value not less than val in list with head h
	inline node* find(node* h, type val){
		for(; h->data < val; h = h->right);
		return h;
	}

	inline node* ffind(node* h, type val){
		node* pos = find(head_top, val);
		for(; pos->below; pos = find(pos->below->left, val));
		return pos;
	}

	// Returns first node with value not less than val (Expected Time: O(log(length)))
	inline node* find(type val){
		return ffind(head, val);
	}

	// Returns value at index (Expected Time: O(log(length)))
	inline type get(int index){
		return VAL_MIN;
	}

	// Adds an element with value val to the list (Expected Time: O(log(length)))
	inline void insert(type val){
		int layers = 1;
		for(int rn = rng() % DEN; rn < NUM; rn = rng() % DEN){
			++layers;
		}
		if(layers > height){
			add_layer();
		}
		int layer = height;
		node *right = find(head_top, val);
		node *left = right->left;
		while(layer > layers){
			right = find(left->below, val);
			left = right->left;
			--layer;
		}
		node* new_node = new node(val);
		left->right = new_node;
		right->left = new_node;
		new_node->left = left;
		new_node->right = right;
		while(left->below){
			right = find(left->below, val);
			left = right->left;
			new_node->below = new node(val);
			new_node->below->above = new_node;
			new_node = new_node->below;
			left->right = new_node;
			right->left = new_node;
			new_node->left = left;
			new_node->right = right;
			--layer;
		}
		++length;
	}

	// Removes the first node with value val from the list if present (Expected Time: O(log(length)))
	inline void remove(type val){
		node* target = find(val);
		if(target->data == val){
			while(target->above){
				target->left->right = target->right;
				target->right->left = target->left;
				target = target->above;
				delete target->below;
			}
			target->left->right = target->right;
			target->right->left = target->left;
			delete target;
			--length;
			while(height > 1 && head_top->right == tail_top){
				head_top = head_top->below;
				delete head_top->above;
				head_top->above = NULL;
				tail_top = tail_top->below;
				delete tail_top->above;
				tail_top->above = NULL;
				--height;
			}
		}
	}

	void print(){
		node* curr = head;
		while(curr){
			int layers = 1;
			node* above = curr;
			while(above->above){
				++layers;
				above = above->above;
			}
			cout << "(" << curr->data << ", " << layers << ") ";
			curr = curr->right;
		}
		cout << "length: " << length << " height: " << height << endl;
	}
};


int main(){
	/*	// IO
	ios_base::sync_with_stdio(false);	// unsync C- and C++-streams (stdio, iostream)
	cin.tie(NULL);	// untie cin from cout (no automatic flush before read)
	*/
    int T;
    cin >> T;
    skiplist<int> sl;
    loop(t, T){
        int a, b;
        cin >> a >> b;
        if(a == 1){
        	sl.insert(b);
        }else{
        	sl.remove(b);
        }
        sl.print();
    }
    return 0;
}
