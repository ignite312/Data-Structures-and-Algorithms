/*
Problem Name: Shortest Routes I
Problem Link: https://cses.fi/problemset/task/1671/
More Problem: https://atcoder.jp/contests/abc362/tasks/abc362_d
              https://codeforces.com/contest/2000/problem/G
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = 1e18;
 
vector<ll> dijkstra(int s, int n, vector<vector<pair<int, ll>>> &adj) {
    vector<ll> dist(n+1, INF);
    dist[s] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({0, s});
    bool vis[n+1];
    memset(vis, false, sizeof(vis));
    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if(vis[u])continue;
        vis[u] = true;
        for(auto [v, wt] : adj[u]) {
            ll _d = d + wt;
            if(_d < dist[v]) {
                dist[v] = _d;
                pq.push({_d, v});
            }
        }
    }
    return dist;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  // cin >> tt;
  while(tt--) {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> adj(n+1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        ll wt;
        cin >> u >> v >> wt;
        adj[u].push_back({v, wt});
    }
    auto d = dijkstra(1, n, adj);
    for(int i = 1; i <= n; i++)cout << d[i] << " ";
        cout << "\n";
  }
  return 0;
}