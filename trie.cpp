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

template<int ALPHABET_SIZE = 26, int MAX_NODES = 1000000>
struct trie{

	int nodes, cnt[MAX_NODES], data[MAX_NODES][ALPHABET_SIZE], wend[MAX_NODES];

	trie() : nodes(0) {
		memset(cnt, 0, MAX_NODES * sizeof(cnt[0]));
		memset(data, 0, MAX_NODES * ALPHABET_SIZE * sizeof(data[0][0]));
		memset(wend, 0, MAX_NODES * sizeof(wend[0]));
	}

	// Must map each char to an index in range [0, ALPHABET_SIZE - 1]
	int index(char c){
		return c - 'a';
	}

	void insert(string s){
		int l = s.size();
		int curr = 0;
		++cnt[0];
		for(int i = 0; i < l; ++i){
			int j = index(s[i]);
			if(!data[curr][j]){
				data[curr][j] = ++nodes;
			}
			curr = data[curr][j];
			++cnt[curr];
		}
		++wend[curr];
	}

	// Returns index of the last node of s in the trie or -1 if s is not present
	int get(string s){
		int l = s.size();
		int curr = 0;
		for(int i = 0; i < l; ++i){
			int j = index(s[i]);
			if(!data[curr][j]){
				return -1;
			}
			curr = data[curr][j];
		}
		return curr;
	}

	int count(string s){
		int i = get(s);
		if(i == -1){
			return 0;
		}
		return wend[i];
	}

};

int main(){
	/*	// IO
	ios_base::sync_with_stdio(false);	// unsync C- and C++-streams (stdio, iostream)
	cin.tie(NULL);	// untie cin from cout (no automatic flush before read)
	*/
    int n, q;
    cin >> n >> q;
    trie<26>* tr = new trie<26>;
    loop(i, n){
    	string s;
    	cin >> s;
    	tr->insert(s);
    }
    loop(i, q){
    	string s;
    	cin >> s;
    	int k = tr->get(s);
    	cout << ((k == -1) ? 0 : tr->cnt[k]) << endl;
    }
    return 0;
}
