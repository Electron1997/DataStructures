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

// Implements multiset semantics
namespace treap{    // prevent conflicts with std

    // RANDOM NUMBER GENERATOR
    // rng() generates u.a.r. from [0, 2^32 - 1]
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    template<typename T = int>
    struct node{

        T data;
        unsigned prio, size, count;
        node *left, *right;

        node(T value, unsigned priority) : data(value), prio(priority), size(1), count(1), left(NULL), right(NULL){}

    };

    template<typename T = int>
    inline unsigned size(node<T> *root){
        if(!root){
            return 0;
        }
        return root->size;
    }

    // Update all variables that depend on children or count (is called whenever children or count could have changed)
    template<typename T = int>
    inline void update(node<T> *root){
        if(root){
            root->size = size(root->left) + root->count + size(root->right);
        }
    }

    template<typename T = int>
    inline node<T> *rotate_left(node<T> *root){
        node<T> *new_root = root->right;
        root->right = new_root->left;
        new_root->left = root;
        return new_root;
    }

    template<typename T = int>
    inline node<T> *rotate_right(node<T> *root){
        node<T> *new_root = root->left;
        root->left = new_root->right;
        new_root->right = root;
        return new_root;
    }

    template<typename T = int>
    node<T> *insert(T value, unsigned priority, node<T> *root){
        if(!root){
            return new node<T>(value, priority);
        }
        if(value == root->data){
            ++root->count;
        }else if(value < root->data){
            root->left = insert(value, priority, root->left);
            if(root->left->prio > root->prio){
                root = rotate_right(root);
                update(root->right);
            }
        }else{
            root->right = insert(value, priority, root->right);
            if(root->right->prio > root->prio){
                root = rotate_left(root);
                update(root->left);
            }
        }
        update(root);
        return root;
    }

    template<typename T = int>
    inline node<T> *insert(T value, node<T> *root){
        unsigned priority = rng();
        if(priority) --priority;    // reserve UINT_MAX for special operations
        return insert(value, priority, root);
    }

    template<typename T = int>
    node<T> *find(T value, node<T> *root){
        while(root && root->data != value){
            if(value < root->data){
                root = root->left;
            }else{
                root = root->right;
            }
        }
        return root;
    }

    template<typename T = int>
    node<T> *get(unsigned index, node<T> *root){
        if(!root){
            return NULL;
        }
        unsigned left_size = size(root->left);
        if(index < left_size){
            return get(index, root->left);
        }
        if(index >= left_size && index < left_size + root->count){
            return root;
        }
        return get(index - left_size - root->count, root->right);
    }

    // Returns lowest index where the element could be inserted (i.e. number of elements smaller than value)
    template<typename T = int>
    unsigned index(T value, node<T> *root){
        if(!root){
            return 0;
        }
        if(value <= root->data){
            return index(value, root->left);
        }
        return size(root->left) + root->count + index(value, root->right);
    }

    template<typename T = int>
    node<T> *remove(T value, node<T> *root){
        if(!root){
            return NULL;
        }
        if(value < root->data){
            root->left = remove(value, root->left);
        }else if(value > root->data){
            root->right = remove(value, root->right);
        }else{
            if(root->count > 1){
                --root->count;
            }else{
                // Ugly part
            }
        }
        // TO DO: when do we call update()?
    }

/*    template<typename T = int>
    std::pair<node<T>*, node<T>*> split(T value, node<T> *root); */

    template<typename T = int>
    std::pair<node<T>*, node<T>*> split(unsigned index, node<T> *root){
        unsigned left_size = size(root->left);  // SegFault if root is NULL
        if(index < left_size){
            auto rec = split(index, root->left);
            root->left = rec.second;
            update(root);
            return {rec.first, root};
        }
        if(index == left_size){
            node<T> *left = root->left;
            root->left = NULL;
            update(root);
            return {left, root};
        }
        if(index < left_size + root->count){
            node<T> *new_root = new node<T>(root->data, root->prio);
            new_root->count = left_size + root->count - index;
            root->count = root->count - new_root->count;
            new_root->right = root->right;
            root->right = NULL;
            update(root);
            update(new_root);
            return {root, new_root};
        }
        if(index == left_size + root->count){
            node<T> *right = root->right;
            root->right = NULL;
            update(root);
            return {root, right};
        }
        auto rec = split(index - left_size - root->count, root->right);
        root->right = rec.first;
        update(root);
        return {root, rec.second};
    }

    // Elements in left <= elements in right must hold! ***
    template<typename T = int>
    node<T> *join(node<T> *left, node<T> *right){
        if(!left){
            return right;
        }
        if(!right){
            return left;
        }
        if(left->data == right->data){  // *** merge nodes of same value
            left->right = right->right;
            left->count += right->count;
            delete right;
            update(left);
            return left;
        }  
        if(left->prio > right->prio){
            left->right = join(left->right, right);
            update(left);
            return left;
        }
        right->left = join(left, right->left);
        update(right);
        return right;
    }

    template<typename T = int>
    void print_data(node<T> *root){
        if(root){
            print_data(root->left);
            cout << root->data << " " << root->count << endl;
            print_data(root->right);
        }
    }

} // End of namespace treap

treap::node<int> *l, *r;

int solve(treap::node<int> *root){
    if(root == NULL)
        return 0;
    int sol = treap::index(root->data, l) + root->count - treap::index(root->data, r);
    return max(sol, max(solve(root->left), solve(root->right)));
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    int n;
    cin >> n;
    loop(i, n){
        int a, b;
        cin >> a >> b;
        l = treap::insert(a, l);
        r = treap::insert(b, r);
    }
    cout << solve(l) << endl;

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
