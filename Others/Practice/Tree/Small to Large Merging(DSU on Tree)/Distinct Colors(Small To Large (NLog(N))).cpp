/*
Problem Name: Distinct Colors
Problem Link: https://cses.fi/problemset/task/1139
Complexity: NLog(N)
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 200001;
int color[N], subtree[N], cnt[N];
int ans[N];
vector<int> adj[N], a[N];
int distinct = 0;
map<int, int> id;
 
void dfs(int u, int p) {
  subtree[u] = 1;
  for(auto v : adj[u]) {
    if(v == p)continue;
    dfs(v, u);
    subtree[u]+=subtree[v];
  }
}
void update(int u, int x) {
  cnt[color[u]]+=x;
  if(x == -1) {
    if(cnt[color[u]] == 0) {
        distinct--;
    }
  }
  if(x == 1) {
    if(cnt[color[u]] == 1) {
        distinct++;
    }
  }
}
void smallToLarge(int u, int p, bool keep) {
  int mx_subtree = -1, bigchild = -1;
  for(auto v : adj[u]) {
    if(v == p)continue;
    if(subtree[v] > mx_subtree) {
      mx_subtree = subtree[v];
      bigchild = v;
    }
   }
   for(auto v : adj[u]) {
    if(v != p && v != bigchild) {
        smallToLarge(v, u, 0);
    }
  }
  if(bigchild != -1) {
    smallToLarge(bigchild, u, 1);
    swap(a[bigchild], a[u]);
  }
 
  a[u].push_back(u);
  update(u, 1);
 
  for(auto v : adj[u]) {
    if(v != p && v != bigchild) {
      for(auto ele : a[v]) {
        update(ele, 1);
        a[u].push_back(ele);
      }
    }
  }
  ans[u] = distinct;
  if(!keep)for(auto ele : a[u])update(ele, -1);
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
        int _id = 0;
        for(int i = 1; i <= n; i++) {
          int x;
          cin >> x;
          if(id[x] == 0) {
            id[x] = ++_id;
          }
          color[i] = id[x];
        }
        for(int i = 0; i < n-1; i++) {
          int u, v;
          cin >> u >> v;;
          adj[u].push_back(v);
          adj[v].push_back(u);
        }
        dfs(1, -1);
        smallToLarge(1, -1, 0);
        for(int i = 1; i <= n; i++)cout << ans[i] << " ";
    }
    return 0;
}