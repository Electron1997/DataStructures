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

template<int N = 100005>
struct dsu {

	int par[N], h[N];

	dsu(int n = N){
		for(int i = 0; i < n; ++i){
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

	// Time: O(n)
	void reset(int n = N){
	    loop(i, n){
	        par[i] = i;
	        h[i] = 1;
	    }
	}

};

int main(){
	/*	// IO
	ios_base::sync_with_stdio(false);	// unsync C- and C++-streams (stdio, iostream)
	cin.tie(NULL);	// untie cin from cout (no automatic flush before read)
	*/
    int n, m, id = 1;
    cin >> n >> m;
    dsu<200005> *uf = new dsu<200005>();
    unordered_map<int, int> mp;
    int sol = n;
    loop(i, m){
    	int u, v;
    	cin >> u >> v;
    	if(!mp[u]){
    		mp[u] = id++;
    	}
    	if(!mp[v]){
    		mp[v] = id++;
    	}
    	if(uf->find(mp[u]) != uf->find(mp[v])){
    		--sol;
    	}
    	uf->join(mp[u], mp[v]);
    }
    cout << sol << endl;
    return 0;
}
