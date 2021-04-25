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

// Maximum number of elements in the DSU
const int N = 100000;

int par[N], h[N];

// Time: O(n)
void init(int n = N){
    loop(i, n){
        par[i] = i;
        h[i] = 1;
    }
}

// Time: ~O(1)
int find(int i){
    if(par[i] != i){
        par[i] = find(par[i]);
    }
    return par[i];
}

// Time: ~O(1)
void join(int i, int j){
    int s = find(i);
    int t = find(j);
    if(s != t){
        if(h[s] > h[t]){
            swap(s, t);
        }
        par[s] = t;
        if(h[s] == h[t]){
            ++h[t];
        }
    }
}

int main(){
	/*	// IO
	ios_base::sync_with_stdio(false);	// unsync C- and C++-streams (stdio, iostream)
	cin.tie(NULL);	// untie cin from cout (no automatic flush before read)
	*/
    int T;
    cin >> T;
    loop(t, T){
        // Solve test case here
    }
    return 0;
}
