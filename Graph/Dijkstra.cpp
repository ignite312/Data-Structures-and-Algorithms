// https://cses.fi/problemset/task/1195/
// Practice: https://codeforces.com/contest/20/problem/C
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = 1e18;

struct Dijkstra {
  int n;
  vector<ll> dist;
  vector<bool> vis;
  Dijkstra(int n): n(n) {
    dist.assign(n + 1, INF);
    vis.assign(n + 1, false);
  }
  vector<ll> run(int s, const vector<vector<pair<int, ll>>> & adj) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
      auto[d, u] = pq.top();
      pq.pop();
      if (vis[u]) continue;
      vis[u] = true;
      for (auto[v, w]: adj[u]) {
        ll nd = d + w;
        if (nd < dist[v]) {
          dist[v] = nd;
          pq.push({nd, v});
        }
      }
    }
    return dist;
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
    vector<vector<pair<int, ll>>> adj(n+1), radj(n+1);
    for (int i = 1; i <= m; i++) {
      int u, v;
      ll wt;
      cin >> u >> v >> wt;
      adj[u].push_back({v, wt});
      radj[v].push_back({u, wt});
    }
    Dijkstra D1(n), D2(n);
    auto da = D1.run(1, adj);
    auto db = D2.run(n, radj);
    ll mn = INF;
    for (int u = 1; u <= n; u++) {
      for (auto v: adj[u]) {
        if (da[u] != INF && db[v.first] != INF) {
          mn = min(mn, da[u] + db[v.first] + v.second/2);
        }
      }
    }
    cout << mn << "\n";
  }
  return 0;
}