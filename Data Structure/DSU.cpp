#include<bits/stdc++.h>
using namespace std;

struct DSU {
    int n, sz;
    vector<int> parent, size;
    DSU(int n){
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for(int i = 0; i <= n; ++i)parent[i] = i;
    }
    void make_set(int v) {
        parent[v] = v; size[v] = 1;
    }
    int find_set(int v){
        if(v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }
    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if(a != b) {
            if (size[a] < size[b])swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
    void reset(int new_n) {
        n = new_n;
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for(int i = 0; i <= n; ++i)parent[i] = i;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        int m1, m2;
        cin >> m1 >> m2;
        set<pair<int, int>> pr1, pr2;

        DSU dsu1(n), dsu2(n);
        for(int i = 0; i < m1; i++) {
            int x, y;
            cin >> x >> y;
            pr1.insert({x, y});
            dsu1.union_sets(x, y);
        }
        for(int i = 0; i < m2; i++) {
            int x, y;
            cin >> x >> y;
            pr2.insert({x, y});
            dsu2.union_sets(x, y);
        }
        int cnt = 0;
        set<pair<int, int>> _new;
        for(auto x : pr1) {
            if(dsu2.find_set(x.first) != dsu2.find_set(x.second)) {
                cnt++;
            }else {
                _new.insert({x.first, x.second});
            }
        }
        dsu1.reset(n);
        for(auto x : _new) {
            dsu1.union_sets(x.first, x.second);
        }
        for(auto x : pr2) {
            if(dsu1.find_set(x.first) != dsu1.find_set(x.second)) {
                cnt++;
                dsu1.union_sets(x.first, x.second);
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}