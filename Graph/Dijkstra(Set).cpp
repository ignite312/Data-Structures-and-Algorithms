/*
Problem Name: Shortest Routes I
Problem Link: https://cses.fi/problemset/task/1671/
More Problem: https://atcoder.jp/contests/abc362/tasks/abc362_d
              https://codeforces.com/contest/2000/problem/G
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100000;
const ll INF = LLONG_MAX;
vector<pair<int, ll>> adj[N+1];
vector<bool> vis(N+1);
vector<ll> d(N+1, INF);
 
void dijkstra(int s) {
    set<pair<ll, int>> st;
    st.insert({0, s});
    d[s] = 0;
    while(st.size() > 0) {
        auto node = *st.begin();
        int u = node.second;
        st.erase(st.begin());
        if(vis[u])continue;
        vis[u] = true;
        for(auto child : adj[u]) {
            int v = child.first;
            ll wt = child.second;
            if(d[u] + wt  < d[v]) {
                d[v] = d[u] + wt;
                st.insert({d[v], v});
            }
        }
    }
    return;
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
        ll wt;
        cin >> u >> v >> wt;
        adj[u].push_back({v, wt});
    }
    dijkstra(1);
    for(int i = 1; i <= n; i++)cout << d[i] << " ";
        cout << "\n";
  }
}
/*
Example where Dijkstra's algorithm fails with negative weights.
7 7
1 2 2
1 3 1000
3 4 1000
4 5 1000
5 2 -5000
2 6 1
6 7 1
*/