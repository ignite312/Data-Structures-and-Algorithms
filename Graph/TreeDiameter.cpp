#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
vector<int> G[N+5];
int depth[N+5];
 
void dfs(int vertex, int parent) {
    for(auto child : G[vertex]) {
        if(child == parent)continue;
        depth[child]=depth[vertex]+1;
        dfs(child, vertex);
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
    for(int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, -1);
    int mx_node = -1, dept_now = -1;
    for(int i = 1; i <= n; i++) {
        if(depth[i] > dept_now) {
            mx_node = i;
            dept_now = depth[i];
        }
        depth[i] = 0;
    }
    dfs(mx_node, -1);
    mx_node = -1, dept_now = -1;
    for(int i = 1; i <= n; i++) {
        if(depth[i] > dept_now) {
            mx_node = i;
            dept_now = depth[i];
        }
    }
    cout << dept_now << "\n";
  }
}
// https://cses.fi/problemset/task/1131\
// https://codeforces.com/contest/1881/problem/F
