// https://cses.fi/problemset/task/1676
#include <bits/stdc++.h>
using namespace std;

struct DSU {
  // 1-based indexing
  int n, sz;
  vector<int> parent, size;
  DSU(int n) {
    parent.resize(n + 1);
    size.resize(n + 1, 1);
    for (int i = 0; i <= n; ++i) parent[i] = i;
  }
  void make_set(int v) {
    parent[v] = v;
    size[v] = 1;
  }
  int find_set(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v]);
  }
  void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      if (size[a] < size[b]) swap(a, b);
      parent[b] = a;
      size[a] += size[b];
    }
  }
  void reset(int new_n) {
    n = new_n;
    parent.resize(n + 1);
    size.resize(n + 1, 1);
    for (int i = 0; i <= n; ++i) parent[i] = i;
  }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  // cin >> tt;
  while (tt--) {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    int now = n, largest = 1;
    for (int i = 1; i <= m; i++) {
      int u, v;
      cin >> u >> v;
      if (dsu.find_set(u) != dsu.find_set(v)) {
        now--;
        dsu.union_sets(u, v);
        largest = max(largest, max(dsu.size[dsu.find_set(u)], dsu.size[dsu.find_set(v)]));
        cout << now << " " << largest << "\n";
      } else cout << now << " " << largest << "\n";
    }
  }
  return 0;
}