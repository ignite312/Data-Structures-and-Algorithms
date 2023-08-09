#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LLONG_MAX;
vector<tuple<int, int, ll>> edges;
int n, m, st = 1;

void BellmanFord() {
    vector<ll> dist(n+1);//don't init INF here
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
