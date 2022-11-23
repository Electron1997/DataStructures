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

// RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0, 2^32 - 1]
mt19937 rng(0);//chrono::steady_clock::now().time_since_epoch().count());

struct node{
    int d, p, s;
    node *l, *r;
    bool f;

    node(int data) : d(data), l(NULL), r(NULL), s(1), f(false){
        p = rng();
    }
};


inline int size(node *r){
    if(!r)
        return 0;
    return r->s;
}

inline void update(node *r){
    if(r){
        r->s = size(r->l) + 1 + size(r->r);
    }
}

inline void pf(node *r){
    if(r->f){
        r->f = false;
        node *u = r->l;
        r->l = r->r;
        r->r = u;
        if(r->l){
            r->l->f = !r->l->f;
        }
        if(r->r){
            r->r->f = !r->r->f;
        }
    }
}

pair<node*, node*> split(int i, node *r){
    if(!r)
        return {NULL, NULL};
    pf(r);
    int ls = size(r->l);
    if(i < ls){
        auto u = split(i, r->l);
        r->l = u.s;
        update(r);
        return {u.f, r};
    }
    if(i > ls){
        auto u = split(i - ls - 1, r->r);
        r->r = u.f;
        update(r);
        return {r, u.s};
    }
    if(i == ls){
        auto l = r->l;
        r->l = NULL;
        update(r);
        return {l, r};
    }
}

node *join(node *l, node *r){
    if(!l)
        return r;
    if(!r)
        return l;
    pf(l); pf(r);
    if(l->p > r->p){
        l->r = join(l->r, r);
        update(l);
        return l;
    }
    r->l = join(l, r->l);
    update(r);
    return r;
}

void print(node *r){
    if(r){
        pf(r);
        print(r->l);
        cout << ((char) r->d);
        print(r->r);
    }
}

node *root = NULL;

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)
    
    int n, m;
    cin >> n >> m;
    loop(i, n){
        char c;
        cin >> c;
        root = join(root, new node(c));
    }
    loop(i, m){
        int a, b;
        cin >> a >> b;
        --a;
        auto r = split(b, root);
        auto l = split(a, r.f);
        l.s->f = true;
        r.f = join(l.f, l.s);
        root = join(r.f, r.s);
    }
    print(root);

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
