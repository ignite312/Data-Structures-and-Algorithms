#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LLONG_MAX;
vector<tuple<int, int, int>> edges;
int n, m, st = 1;

void BellmanFord() {
    vector<ll> dist(n+1, INF);
    vector<int> parent(n+1, -1);
    dist[st] = 0;
    for (;;) {
        bool any = false;
        for (auto[u, v, cost] : edges)
            if (dist[u] < INF)
                if (dist[v] > dist[u] + cost) {
                    dist[v] = dist[u] + cost;
                    parent[v] = u;
                    any = true;
                }
        if (!any)
            break;
    }
    if (dist[n] == INF)
        cout << "-1\n";
    else {
        vector<int> path;
        for (int cur = n; cur != -1; cur = parent[cur])
            path.push_back(cur);
        reverse(path.begin(), path.end());
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
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        ll cost;
        cin >> u >> v >> cost;
        edges.emplace_back(u, v, cost);
        // edges.emplace_back(v, u, cost);if undirected
    }
    BellmanFord();
  }
}
// https://codeforces.com/contest/20/submission/218048541
