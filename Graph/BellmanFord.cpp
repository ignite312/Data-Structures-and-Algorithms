#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LLONG_MAX;
vector<tuple<int, int, int>> edges;
int n, m, st = 1;

void BellmanFord() {
    vector<ll> dist(n+1, INF);
    dist[st] = 0;
    for (;;) {
        bool any = false;
        for (auto[u, v, cost] : edges)
            if (dist[u] < INF)
                if (dist[v] > dist[u] + cost) {
                    dist[v] = dist[u] + cost;
                    any = true;
                }
        if (!any)
            break;
    }
    for(int i = 1; i <= n; i++) {cout << dist[i] << " ";}
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
    }
    BellmanFord();
  }
}
// https://cses.fi/problemset/task/1671
