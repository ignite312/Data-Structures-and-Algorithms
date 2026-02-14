/*
Problem Name: Round Trip II
Problem Link: https://cses.fi/problemset/task/1678/
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 100001;
vector<int> adj[N], parent(N);
vector<bool> visited(N), inStack(N);
int st, en;

bool dfs(int u, vector<int> &path, vector<int> &cyc) {
    visited[u] = inStack[u] = true;
    path.push_back(u);
    for(auto v : adj[u]) {
        if(!visited[v]) {
            if(dfs(v, path, cyc)) return true;
        }else if(inStack[v]) {
          auto it = find(path.begin(), path.end(), v);
          cyc.assign(it, path.end());
          cyc.push_back(v);
          return true;
        }
    }
    inStack[u] = false;
    path.pop_back();
    return false;
}
void checkCycle(int n) {
    vector<int> path, cyc;
    for(int i = 1; i <= n; i++) {
        if(!visited[i] && dfs(i, path, cyc)) {
            break;
        }
    }
    if(cyc.empty()) cout << "IMPOSSIBLE\n";
    else {
      cout << cyc.size() << "\n";
      for(auto x : cyc) {
        cout << x << " ";
      }
    }
}
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  while(tt--) {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    checkCycle(n);
  }
  return 0;
}