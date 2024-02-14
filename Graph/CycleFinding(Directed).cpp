#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
vector<int> G[N+5], parent(N+5);
vector<int> color(N+5);
int st, en;

bool dfs(int vertex) {
    color[vertex] = 1;
    for(auto child : G[vertex]) {
        if(!color[child]) {
            parent[child] = vertex;
            if(dfs(child)) return true;
        }else if(color[child] == 1) {
            st = child, en = vertex;
            return true;
        }
    }
    color[vertex] = 2;
    return false;
}
void checkCycle(int n) {
    st = en = -1;
    for(int i = 1; i <= n; i++) {
        if(!color[i] && dfs(i)) {
            break;
        }
    }
    if(st == -1) cout << "IMPOSSIBLE\n";
    else {
        vector<int> path;
        path.push_back(st);
        for(int i = en; i != st; i = parent[i])path.push_back(i);
        path.push_back(st);
        reverse(path.begin(), path.end());
        cout << path.size() << "\n";
        for(auto i : path)cout << i << " ";
        cout << "\n";
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
        G[u].push_back(v);
    }
    checkCycle(n);
  }
  return 0;
}
// https://cses.fi/problemset/task/1678/
// https://codeforces.com/contest/1931/problem/F
