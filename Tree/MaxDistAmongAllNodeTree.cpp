/*
Problem Name: Tree Distances I
Problem Link: https://cses.fi/problemset/task/1132
Idea:Tree Re-rooting 
More Problem: https://codeforces.com/contest/1187/problem/E
More Problem: https://atcoder.jp/contests/dp/tasks/dp_v
More Problem: https://codeforces.com/contest/1822/problem/F
More Problem: https://atcoder.jp/contests/abc368/submissions/57074317
More Problem: https://cses.fi/problemset/task/1133/
More Problem: https://codeforces.com/gym/106208/problem/G
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 200001;
vector<int> adj[N];
int down[N], up[N]; 
 
void dfs1(int u, int p) {
    for(auto v : adj[u]) {
        if(v == p)continue;
        dfs1(v, u);
        down[u] = max(down[u], down[v] + 1);
    }
}
void dfs2(int u, int p) {
    int mx = -2;
    for(auto v : adj[u]) {
        if(v == p) {
            continue;
        }
        up[v] = max(up[v], mx+2);
        mx = max(mx, down[v]);
    }
    reverse(adj[u].begin(), adj[u].end());
    mx = -2;
    for(auto v : adj[u]) {
        if(v == p) {
            continue;
        }
        up[v] = max(up[v], mx+2);
        mx = max(mx, down[v]);
    }
    for(auto v : adj[u]) {
        if(v == p) {
            continue;
        }
        up[v] = max(up[v], up[u]+1);
        dfs2(v, u);
    }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  while(tt--) {
    int n;
    cin >> n;
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1, -1);
    dfs2(1, -1);
    for(int i = 1; i <= n; i++)cout << max(down[i], up[i]) << " ";
  }
  return 0;
}