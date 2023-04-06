#include <bits/stdc++.h>

#define f first
#define s second
#define loop(i, n) for (int i = 0; i < n; ++i)
#define read(a, n) loop($, n) cin >> a[$];
#define show(a, n)                  \
    loop($, n) std::cout << a[$] << " "; \
    std::cout << endl;

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

/*  // SET WITH INDEXING
// Implements logarithmic find_by_order() and order_of_key()
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;
*/

/*  // RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0, 2^32 - 1]
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
*/

template<typename TYPE>
struct tensor{
    std::vector<size_t> shape;
    std::vector<TYPE> data;
    tensor(std::vector<size_t> shape){
        this->shape = shape;
        size_t data_size = 1;
        for(auto w : shape){
            data_size *= w;
        }
        data.resize(data_size);
    }
    size_t loc(std::vector<size_t> index){
        size_t stride = 1, i = 0;
        for(size_t k = shape.size() - 1;; --k){
            i += index[k] * stride;
            stride *= shape[k];
            if(!k) break;
        }
        return i;
    }
    TYPE get(std::vector<size_t> index){
        return data[loc(index)];
    }
    void set(std::vector<size_t> index, TYPE value){
        data[loc(index)] = value;
    }
    // Provisional (ugly and ineff)
    void print(std::vector<size_t> &index, size_t dim = 0){
        if(dim == shape.size()){
            std::cout << data[loc(index)] << " ";
            return;
        }
        for(index[dim] = 0; index[dim] < shape[dim]; ++index[dim]){
            if(dim == shape.size() - 3){
                for(size_t i = 0; i < shape.size() - 2; ++i){
                    std::cout << index[i] << " ";
                }
                std::cout << ":" << endl;
            }
            print(index, dim + 1);
            if(dim < shape.size() - 1) std::cout << endl;
        }
        index[dim] = 0;
    }
};

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    // ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    // cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    tensor<int> A({2, 3, 4, 5});
    loop(i, 120){
        A.data[i] = i + 1;
    }
    A.set({1, 2, 3, 4}, -10);
    vector<size_t> aux(4);
    A.print(aux);
    std::cout << A.get({1, 0, 3, 2}) << endl;

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    std::cout << duration.count() << endl;
    */
    return 0;
}