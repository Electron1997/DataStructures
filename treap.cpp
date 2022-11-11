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

/*  // RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0, 2^32 - 1]
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
*/

// Implements set semantics
template<class type = int>
struct treap{

    struct node{
        type data;
        int priority;
        node *left, *right;

        node(type val) : data(val), priority(rng()), left(NULL), right(NULL) {}
    };

    mt19937 rng;

    node *root;

    treap() : rng(mt19937(chrono::steady_clock::now().time_since_epoch().count())), root(NULL) {}

    inline node *rotate_left(node *pivot){
        node *new_root = pivot->right;
        pivot->right = new_root->left;
        new_root->left = pivot;
        return new_root;
    }

    inline node *rotate_right(node *pivot){
        node *new_root = pivot->left;
        pivot->left = new_root->right;
        new_root->right = pivot;
        return new_root;
    }

    inline void insert(type val){};

    inline void remove(type val);

    inline void join(treap<type> other);

    inline void split(type val);
};

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    int T;
    cin >> T;
    loop(t, T){
        // Solve test case here
    }

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
