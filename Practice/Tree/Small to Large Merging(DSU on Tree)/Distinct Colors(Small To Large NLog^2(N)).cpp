/*
Problem Name: Distinct Colors
Problem Link: https://cses.fi/problemset/task/1139
Another Problem: https://codeforces.com/contest/1923/problem/E
Complexity: NLog^2(N)
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 1;
int color[N], distinct[N];
vector<int> adj[N];
vector<set<int>> s(N);
 
void dfs(int u, int p) {
  s[u] = {color[u]};
  for (auto v: adj[u]) {
    if (v == p)  continue;
    dfs(v, u);
    if (s[u].size() < s[v].size()) {
      s[u].swap(s[v]);
    }
    for (auto x: s[v]) {
      s[u].insert(x);
    }
  }
  distinct[u] = s[u].size();
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++) {
          cin >> color[i];
        }
        for(int i = 0; i < n-1; i++) {
          int u, v;
          cin >> u >> v;;
          adj[u].push_back(v);
          adj[v].push_back(u);
        }
        dfs(1, -1);
        for(int i = 1; i <= n; i++)cout << distinct[i] << " ";
    }
    return 0;
}