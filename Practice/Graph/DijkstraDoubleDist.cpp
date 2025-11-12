// https://codeforces.com/problemset/problem/2014/E
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = 1e18;
const int N = 2e5 + 1;
bool horses[N];
 
vector<ll> dijkstra(int s, int n, vector<vector<array<ll, 2>>> &adj) {
    vector<array<ll, 2>> dist(n+1, {INF, INF});
    dist[s][0] = 0;
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;
    pq.push({0, s, 0});
    int vis[n+1][2];
    memset(vis, false, sizeof(vis));
    while(!pq.empty()) {
        auto [d, u, flag] = pq.top();
        pq.pop();
        if(vis[u][flag])continue;
        vis[u][flag] = true;
        flag |= horses[u];
        for(auto [v, wt] : adj[u]) {
            ll _d = d;
            if(flag)_d+=wt/2;
            else _d+=wt;
            if(_d < dist[v][flag]) {
                dist[v][flag] = _d;
                pq.push({_d, v, flag});
            }
        }
    }
    vector<ll> ret(n+1);
    for(int i = 1; i <= n; i++) {
        ret[i] = min(dist[i][0], dist[i][1]);
    }
    return ret;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  cin >> tt;
  while(tt--) {
    int n, m, h;
    cin >> n >> m >> h;
    for(int i = 1; i <= n; i++) {
        horses[i] = false;
    }
    for(int i = 0; i < h; i++) {
        ll f;
        cin >> f;
        horses[f] = true;
    }
    vector<vector<array<ll, 2>>> adj(n+1);
    for(int i = 0; i < m; i++) {
        int u, v;
        ll wt;
        cin >> u >> v >> wt;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    auto d1 = dijkstra(1, n, adj);
    auto d2 = dijkstra(n, n, adj);
    ll ans = INF;
    for(int i = 1; i <= n; i++) {
        ans = min(ans, max(d1[i], d2[i]));
    }
    if(ans != INF)cout << ans << "\n";
    else cout << -1 << "\n";
  }
  return 0;
}