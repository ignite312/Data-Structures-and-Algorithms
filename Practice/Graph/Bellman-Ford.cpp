/*
Problem Name: Shortest Routes I
Problem Link: https://cses.fi/problemset/task/1671/
*/

// This implementation will give TLE just to confirm that out algorithm are working perfectly
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = LLONG_MAX;
vector<tuple<int, int, ll>> edges;

void BellmanFord(int s, int n) {
    vector<ll> dist(n + 1, INF);
    dist[s] = 0;  
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
/*
Example where the Bellman-Ford algorithm works with negative weights.
7 7
1 2 2
1 3 1000
3 4 1000
4 5 1000
5 2 -5000
2 6 1
6 7 1
*/