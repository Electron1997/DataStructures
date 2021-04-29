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

		node *left, *right, *above, *below;
		type data;
		int link_length;	// Length of the link from this node to the node to its right
	
		node(type val) : left(NULL), right(NULL), above(NULL), below(NULL), data(val), link_length(0){}
	};

	// rng() generates u.a.r. from [0, 2^32 - 1]
	mt19937 rng;

	// length : number of elements in list (not counting sentinels), height : number of layers
	int length, height;

	node *head, *head_top, *tail, *tail_top;

	// Initializes rng, sets up sentinels
	skiplist() : length(0), height(1), rng(mt19937(chrono::steady_clock::now().time_since_epoch().count())){
		head = head_top = new node(VAL_MIN);
		tail = tail_top = new node(VAL_MAX);
		head->right = tail;
		tail->left = head;
		head->link_length = 1;
	}
	
	inline node* add_above(node *h, type val){
		h->above = new node(val);
		h->above->below = h;
		return h->above;
	}

	inline void add_layer(){ 
		head_top = add_above(head_top, VAL_MIN);
		tail_top = add_above(tail_top, VAL_MAX);
		head_top->right = tail_top;
		tail_top->left = head_top;
		head_top->link_length = length + 1;
		++height;
	}

	inline node* delete_top(node *top){
		top = top->below;
		delete top->above;
		top->above = NULL;
		return top;
	}

	// Links pos.left<->new_node<->pos (does not set link lengths)
	inline void link(node *new_node, node *pos){
		new_node->left = pos->left;
		new_node->right = pos;
		new_node->left->right = new_node;
		new_node->right->left = new_node;
	}

	// left<->target<->right --> left<->right (updates link lengths)
	inline void unlink(node *target){
		target->left->link_length += target->link_length - 1;
		target->left->right = target->right;
		target->right->left = target->left;
	}

	// Finds rightmost node with value less than val in list with head h (linear single layer search)
	inline node* find(node *h, type val){
		while(h->right->data < val){
			h = h->right;
		}
		return h;
	}

	// Finds rightmost node with value less than val in the skiplist with head top h (multilayer search)
	inline node* ffind(node *h, type val){
		node *pos = find(head_top, val);
		while(pos->below){
			pos = find(pos->below, val);
		}
		return pos;
	}

	// Returns first node with value not less than val (Expected Time: O(log(length)))
	inline node* find(type val){
		return ffind(head, val)->right;
	}

	// Returns value at index (Expected Time: O(log(length)))
	inline type get(int index){
		int i = -1;	// Offset for 0-based indexing
		node *curr = head_top;
		while(i < index){
			if(i + curr->link_length <= index){
				i += curr->link_length;
				curr = curr->right;
			}else{
				curr = curr->below;
			}
		}
		return curr->data;
	}

	// Adds an element with value val to the list (Expected Time: O(log(length)))
	inline void insert(type val){
		int layers = 1;
		for(int rn = rng() % DEN; rn < NUM; rn = rng() % DEN){
			++layers;
		}
		if(layers > height){
			add_layer();
			layers = height;	// Increase height at most by one (heuristic)
		}

		// Update lower layers
		node *new_node = new node(val), *pos = find(val);
		new_node->link_length = 1;
		link(new_node, pos);
		for(int layer = 2, link_length = 1; layer <= layers; ++layer){
			while(!pos->above){
				link_length += pos->link_length;
				pos = pos->right;
			}
			pos = pos->above;
			new_node = add_above(new_node, val);
			new_node->link_length = link_length;
			pos->left->link_length = pos->left->link_length - link_length + 1;
			link(new_node, pos);
		}

		// Update link lengths in upper layers
		for(int layer = layers + 1; layer <= height; ++layer){
			while(!pos->above){
				pos = pos->right;
			}
			pos = pos->above;
			++pos->left->link_length;
		}

		++length;
	}

	// Removes the first node with value val from the list if present (Expected Time: O(log(length)))
	inline void remove(type val){
		node* target = find(val);
		if(target->data == val){
			int layer = 1;

			// Update lower layers
			while(target->above){
				unlink(target);
				target = target->above;
				delete target->below;
				++layer;
			}
			node *pos = target->left;
			unlink(target);
			delete target;
			++layer;

			// Update link_lengths in upper layers
			while(layer <= height){
				while(!pos->above){
					pos = pos->left;
				}
				pos = pos->above;
				--pos->link_length;
				++layer;
			}

			// Remove redundant layers
			while(height > 1 && head_top->right == tail_top){
				head_top = delete_top(head_top);
				tail_top = delete_top(tail_top);
				--height;
			}

			--length;
		}
	}

	void print(){
		node* curr = head;
		int i = -1;
		while(curr){
			cout << i << " val: " << curr->data << " link_lenghts: " << curr->link_length << " ";
			int layers = 1;
			node* above = curr;
			while(above->above){
				++layers;
				above = above->above;
				cout << above->link_length << " ";
			};
			curr = curr->right;
			++i;
			cout << endl;
		}
		cout << "length: " << length << " height: " << height << endl << endl;
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
        	sl.print();
        }else if(a == 2){
        	sl.remove(b);
        	sl.print();
        }else{
        	cout << sl.get(b) << endl;
        }
    }
    return 0;
}
