// https://codeforces.com/contest/20/problem/C
// This implementation will give TLE just to confirm that out algorithm are working perfectly
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = LLONG_MAX;
vector<tuple<int, int, int>> edges;

void BellmanFord(int st, int n) {
    vector<ll> dist(n+1, INF);
    vector<int> parent(n+1, -1);
    dist[st] = 0;
    for (int i = 0; i < n-1; i++) {
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
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        ll cost;
        cin >> u >> v >> cost;
        edges.emplace_back(u, v, cost);
        edges.emplace_back(v, u, cost);
    }
    BellmanFord(1, n);
  }
  return 0;
}
