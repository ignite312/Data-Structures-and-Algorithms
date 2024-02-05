#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
vector<int> G[N];
int height[N], dist[N]; 
 
void dfs1(int vertex, int parent) {
    for(auto child : G[vertex]) {
        if(child == parent)continue;
        dfs1(child, vertex);
        height[vertex] = max(height[vertex], height[child] + 1);
    }
}
void dfs2(int vertex, int parent) {
    vector<int> ht;
    for(auto child : G[vertex]) {
        if(child == parent)continue;
        ht.push_back(height[child]);
    }
    sort(ht.rbegin(), ht.rend());
    for(auto child : G[vertex]) {
        if(child == parent)continue;
        if(ht.size()  >= 2) dist[child] = max(dist[vertex]+1, (height[child] == ht[0] ? ht[1] : ht[0]) + 2);
        else if(ht.size() == 1) dist[child] = dist[vertex] + 1;
        dfs2(child, vertex);
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
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs1(1, -1);
    dfs2(1, -1);
    for(int i = 1; i <= n; i++)cout << max(height[i], dist[i]) << " ";
  }
}
// https://cses.fi/problemset/task/1132
// https://codeforces.com/contest/1822/problem/F
