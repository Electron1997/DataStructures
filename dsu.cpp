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
typedef tuple<int, int, int, int> edge;	// weight, index, u, v
typedef tuple<int, int, int> query;	// weight, index, v

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

	int par[N], size[N];

	dsu(int n = N){
		for(int i = 0; i < n; ++i){
			par[i] = i;
			size[i] = 1;
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
	        if(size[s] > size[t]){
	            swap(s, t);
	        }
	        par[s] = t;
	        size[t] += size[s];
	    }
	}

	// Time: O(n)
	void reset(int n = N){
	    loop(i, n){
	        par[i] = i;
	        size[i] = 1;
	    }
	}

};

int main(){
	/*	// IO
	ios_base::sync_with_stdio(false);	// unsync C- and C++-streams (stdio, iostream)
	cin.tie(NULL);	// untie cin from cout (no automatic flush before read)
	*/
    int n, m, q;
    cin >> n >> m >> q;
    edge e[m];
    loop(i, m){
    	int u, v, w;
    	cin >> u >> v >> w;
    	e[i] = {w, i, u, v};
    }
    sort(e, e + m, greater<edge>());
    query qu[q];
    loop(i, q){
    	int v, w;
    	cin >> v >> w;
    	qu[i] = {w, i, v};
    }
    sort(qu, qu + q, greater<query>());
    dsu<> *uf = new dsu<>(n);
    int k = 0, sol[q];
    loop(i, q){
    	while(k < m && get<0>(e[k]) >= get<0>(qu[i])){
    		uf->join(get<2>(e[k]), get<3>(e[k]));
    		++k;
    	}
    	sol[get<1>(qu[i])] = uf->size[uf->find(get<2>(qu[i]))];
    }
    loop(i, q){
    	cout << sol[i] << endl;
    }
    return 0;
}
