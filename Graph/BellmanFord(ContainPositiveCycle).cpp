#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = LLONG_MAX;
const int N = 2500+1;
vector<tuple<int, int, ll>> edges;
bool mark[N+1], vis[N+1];
vector<int> G[N+1];
vector<ll> dist(N+1, -INF);
 
void BellmanFord(int st, int n) {
    dist[st] = 0;
    for(int i = 0; i < n-1; i++) {
        bool any = false;
        for(auto[u, v, wt] : edges) {
            if(dist[u] > -INF) {
                if(dist[u] + wt > dist[v]) {
                    dist[v] = dist[u] + wt;
                    any = true;
                }
            }
        }
        if(!any)break;
    }
    for(auto[u, v, wt] : edges)
        if(dist[u] > -INF)
            if(dist[u] + wt > dist[v])
                mark[v] = true;
}
void dfs(int vertex) {
    vis[vertex] = true;
    for(auto child : G[vertex])
        if(!vis[child])
            dfs(child);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    while(tt--) {
        int n, m;
        cin >> n >> m;
        for(int i = 0; i < m; i++) {
            int u, v;
            ll wt;
            cin >> u >> v >> wt;
            G[u].push_back(v);
            edges.emplace_back(u, v, wt);
        }
        BellmanFord(1, n);
        for(int i = 1; i <= n; i++) {
            if(mark[i]) {
                for(int i = 0; i <= n; i++)vis[i] = false;
                dfs(i);
                if(vis[n]) {
                    cout << "-1";
                    return 0;
                }
            }
        }
        cout << dist[n] << "\n";
    }
    return 0;
}
// https://cses.fi/problemset/task/1673
