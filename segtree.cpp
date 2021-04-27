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

// N : number of nodes in the segtree (2^20 = 1048576)
template<class type = ll, int N = 1048576>
struct segtree{

	// E: neutral element (set by build_tree())
	type E, tree[N];

	// Associative operation
	type op(const type& a, const type& b){
		return a + b;
	}

	// Time: O(N)
	void build_tree(type a[], int n, type e, bool pow2 = false){
		E = e;
		int M = N / 2;
		for(int i = 0; i < n; ++i){
			tree[M + i] = a[i];
		}
		for(int i = M + n; i < N; ++i){
			tree[i] = E;
		}
		for(int i = M - 1; i > 0; --i){
			tree[i] = op(tree[2 * i], tree[2 * i + 1]);
		}
	}

	// Gets value for range [l, r[ (Time: O(log(N)))
	type range(int l, int r, int L = 0, int R = N / 2, int i = 1){
		if(r <= L || l >= R){
			return E;
		}
		if(l <= L && r >= R){
			return tree[i];
		}
		int M = (L + R) / 2;
		type val = E;
		val = op(val, range(l, min(M, r), L, M, i * 2));
		val = op(val, range(max(M, l), r, M, R, i * 2 + 1));
		return val;
	}

	// Sets i-th element to v (Time: O(log(N)))
	void update(int i, type v){
		i += N / 2;
		tree[i] = v;
		while(i >= 2){
			i /= 2;
			tree[i] = op(tree[i * 2], tree[i * 2 + 1]);
		}
	}
};

int main(){
	/*	// IO
	ios_base::sync_with_stdio(false);	// unsync C- and C++-streams (stdio, iostream)
	cin.tie(NULL);	// untie cin from cout (no automatic flush before read)
	*/
    int n, m;
    cin >> n >> m;
    ll a[n];
    read(a, n);
    segtree<>* S = (segtree<>*) malloc(sizeof(segtree<>));
    S->build_tree(a, n, 0);
    loop(i, m){
    	int q;
    	cin >> q;
    	if(q == 1){
    		int i, v;
    		cin >> i >> v;
    		S->update(i, v);
    	}else{
    		int l, r;
    		cin >> l >> r;
    		cout << S->range(l, r) << endl;
    	}
    }
    return 0;
}
