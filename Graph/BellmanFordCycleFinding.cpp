#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = LLONG_MAX;
vector<tuple<int, int, ll>> edges;

void BellmanFord(int st, int n) {
    vector<ll> dist(n+1);// Don't init INF here because there can be a negative cycle where you can't reach from node 1
    vector<int> parent(n+1, -1);
    dist[st] = 0;
    int flag;
    for (int i = 0; i < n; i++) {
        flag = -1;
        for (auto[u, v, cost] : edges)
            if (dist[u] < INF)
                if (dist[v] > dist[u] + cost) {
                    dist[v] = dist[u] + cost;
                    parent[v] = u;
                    flag = v;
                }
    }
    if (flag == -1)
        cout << "NO\n";
    else {
        int y = flag;
        for (int i = 0; i < n; ++i)
            y = parent[y];

        vector<int> path;
        for (int cur = y;; cur = parent[cur]) {
            path.push_back(cur);
            if (cur == y && path.size() > 1)
                break;
        }
        reverse(path.begin(), path.end());
        cout << "YES\n";
        for (int u : path)
            cout << u << ' ';
    }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  while(tt--) {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        ll cost;
        cin >> u >> v >> cost;
        edges.emplace_back(u, v, cost);
        // edges.emplace_back(v, u, cost);if undirected
    }
    BellmanFord(1, n);
  }
}
// https://cses.fi/problemset/task/1197
