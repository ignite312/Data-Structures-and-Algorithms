/*
Problem Name: V - Subtree
Problem Link: https://atcoder.jp/contests/dp/tasks/dp_v
More Problem: https://codeforces.com/contest/1187/problem/E
More Problem: https://cses.fi/problemset/task/1132
More Problem: https://codeforces.com/contest/1822/problem/F
More Problem: https://atcoder.jp/contests/abc368/submissions/57074317
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 100000;
int n, mod;
vector<int> adj[N];
// up[i] = total ways to paint all the ancestors of node i 
// if the parent of node i is painted black.
vector<ll> up(N, 1);
// down[i] = total ways to paint the subtree of node i 
// if the node i is painted black or white.
ll down[N];

void dfs1(int u, int parent) {
  down[u] = 1;
  for(auto v : adj[u]) {
    if(v == parent)continue;
    dfs1(v, u);
    down[u] = (down[u] * down[v]) % mod;
  }
  down[u] = (down[u] + 1) % mod;
}

void dfs2(int u, int parent) {
  int pref = 1;
  for(auto v : adj[u]) {
    if(v == parent)continue;
    up[v] = pref % mod;
    pref = pref*down[v] % mod;
  }
  reverse(adj[u].begin(), adj[u].end());
  int suff = 1;
  for(auto v : adj[u]) {
    if(v == parent)continue;
    up[v] = up[v]*suff % mod;
    suff = suff*down[v] % mod;
  }
  for(auto v : adj[u]) {
    if(v == parent)continue;
    up[v] = up[u] * up[v] % mod;
    up[v] = (up[v] + 1) % mod;
    dfs2(v, u);
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  // cin >> tt;
  while(tt--) {
    cin >> n >> mod;
    for(int i = 0; i < n-1; i++) {
      int u, v;
      cin >> u >> v;
      --v, --u;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    dfs1(0, -1);
    dfs2(0, -1);
    for(int i = 0; i < n; i++) {
      cout << up[i]*(down[i] - 1 + mod) % mod << "\n";
    }
  }
  return 0;
}