#include<bits/stdc++.h>
using namespace std;

#define ll long long
const ll INF = LLONG_MAX;
vector<tuple<int, int, ll>> edges;

void BellmanFord(int st, int n) {
    vector<ll> dist(n + 1, INF);
    dist[st] = 0;  
    for (int i = 0; i < n - 1; i++) {
        bool any = false;  
        for (auto [u, v, wt] : edges) {
            if (dist[u] < INF) {
                if (dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                    any = true;
                }
            }
        }
        if(!any)break;
    }
    for(int i = 1; i <= n; i++) {cout << dist[i] << " ";}   
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int tt;
    tt = 1;    
    while (tt--) {
        int n, m;
        cin >> n >> m;       
        for (int i = 0; i < m; i++) {
            int u, v;
            ll wt;
            cin >> u >> v >> wt;
            edges.emplace_back(u, v, wt);
        }
        BellmanFord(1, n);
    }
    return 0;
}
// https://cses.fi/problemset/task/1671
