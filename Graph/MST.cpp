#include<bits/stdc++.h>

using namespace std;

struct DSU {
  // 1-based indexing
  int n, sz;
  vector < int > parent, size;
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

int primMST(int V, vector < vector < pair < int, int >>> & adj) {
  priority_queue < pair < int, int > , vector < pair < int, int >> , greater < >> pq;
  vector < bool > inMST(V, false);

  int mstWeight = 0;
  pq.push({
    0,
    0
  }); // {weight, node}

  while (!pq.empty()) {
    auto[wt, u] = pq.top();
    pq.pop();

    if (inMST[u]) continue;

    inMST[u] = true;
    mstWeight += wt;

    for (auto[v, w]: adj[u]) {
      if (!inMST[v]) {
        pq.push({
          w,
          v
        });
      }
    }
  }
  return mstWeight;
}

int kruskal(int n, vector < array < int, 3 >> & edges) {
  // n = number of vertices
  // edges = {weight, u, v}
  sort(edges.begin(), edges.end());
  DSU dsu(n);
  int mst_weight = 0;

  for (auto & [w, u, v]: edges) {
    if (dsu.find_set(u) != dsu.find_set(v)) {
      dsu.union_sets(u, v);
      mst_weight += w;
      // optionally: store edge in MST
      // mst_edges.push_back({u, v, w});
    }
  }
  return mst_weight;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    vector < int > v(n);
    for (int i = 0; i < n; i++) {
      cin >> v[i];
    }
  }
  return 0;
}