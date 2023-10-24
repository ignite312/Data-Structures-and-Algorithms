#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int parent[N+5], Size[N+5];

void make_set(int v) {
    parent[v] = v;
    Size[v] = 1;
    //rank[v] = 0;
}
int find_set(int v) {
    if (v == parent[v])return v;
    return parent[v] = find_set(parent[v]);
}
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if(Size[a] < Size[b])swap(a, b);
        parent[b] = a;
        Size[a]+=Size[b];
    }
}
// Union by Rank
// void union_sets(int a, int b) {
//     a = find_set(a);
//     b = find_set(b);
//     if (a != b) {
//         if (rank[a] < rank[b])
//             swap(a, b);
//         parent[b] = a;
//         if (rank[a] == rank[b])
//             rank[a]++;
//     }
// }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        int n, m;
        cin >> n >> m;
        for(int i = 1; i <= n; i++) {make_set(i);}
        int now = n, largest = 1;
        for(int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            if(find_set(u) != find_set(v)) {
                now--;
                union_sets(u, v);
                largest = max(largest, max(Size[find_set(u)], Size[find_set(v)]));
                cout << now << " " << largest << "\n"; 
            }else cout << now << " " << largest << "\n"; 
        }
    }
    return 0;
}
// https://cses.fi/problemset/result/7487935/
