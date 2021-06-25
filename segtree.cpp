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

// N : maximum number of elements in the segtree
template<class type = ll, int N = 100005>
struct segtree{

	// E: neutral element
	type E, tree[N << 1];

	// Associative operation
	type op(const type& a, const type& b){
		return a + b;
	}

	// Time: O(N)
	segtree(type a[], int n, type e) : E(e){
		for(int i = 0; i < n; ++i){
			tree[N + i] = a[i];
		}
		for(int i = N + n; i < N << 1; ++i){
			tree[i] = E;
		}
		for(int i = N - 1; i > 0; --i){
			tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
		}
	}

	// Gets value for range [l, r[ (Time: O(log(N)))
	type range(int l, int r){
		type val = E;
		for(l += N, r += N; l < r; l >>= 1, r >>= 1){
			if(l & 1){
				val = op(val, tree[l++]);
			}
			if(r & 1){
				val = op(val, tree[--r]);
			}
		}
		return val;
	}

	// Sets i-th element to v (Time: O(log(N)))
	void update(int i, type v){
		for(tree[i += N] = v; i > 0; i >>= 1){
			tree[i >> 1] = op(tree[i], tree[i ^ 1]);
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
    segtree<ll> *st = new segtree<ll>(a, n, 0);
    loop(i, m){
    	int q;
    	cin >> q;
    	if(q == 1){
    		int i, v;
    		cin >> i >> v;
    		st->update(i, v);
    	}else{
    		int l, r;
    		cin >> l >> r;
    		cout << st->range(l, r) << endl;
    	}
    }
    return 0;
}
