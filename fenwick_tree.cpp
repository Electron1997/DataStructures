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

// Fenwick tree (uses 1-based indexing !!!)
template<typename T, size_t N, T Z = 0>
struct fenwick_tree{

    T bit[N + 1];

    fenwick_tree(){
        for(int i = 0; i <= N; ++i){
            bit[i] = Z;
        }
    }

    // Must be commutative and associative
    inline T op(const T& a, const T& b){
        return a + b;
    }

    inline void add(const T& a, int i){
        while(i <= N){
            bit[i] = op(bit[i], a);
            i += i & -i;
        }
    }

    inline T prefix(int i){
        T s = Z;
        while(i){
            s = op(bit[i], s);
            i -= i & -i;
        }
        return s;
    }
};

const int N = 2e5 + 5;

fenwick_tree<ll, N> BIT;

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    int n, q; cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        ll u; cin >> u;
        BIT.add(u, i);
        BIT.add(-u, i + 1);
    }
    loop(i, q){
        int t; cin >> t;
        if(t == 1){
            int l, r; ll u; cin >> l >> r >> u;
            BIT.add(u, l);
            BIT.add(-u, r + 1);
        }else{
            int k; cin >> k;
            cout << BIT.prefix(k) << endl;
        }
    }

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
