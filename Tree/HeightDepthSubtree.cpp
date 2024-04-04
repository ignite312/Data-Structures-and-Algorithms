#include <bits/stdc++.h>
using namespace std;
const int N = 200000;
vector<int> G[N+1], depth(N+1), height(N+1), subtree(N+1);
bool vis[N];

void dfs(int u, int p) {
    subtree[u] = 1;
    for(auto v : G[u]) {
        if(v == p)continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
        subtree[u] += subtree[v];
        height[u] = max(height[u], height[v] + 1);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        } 
        dfs(1, -1);
        for (int i = 1; i <= n; ++i)
            cout << depth[i] << " " << height[i] << " " << subtree[i] << "\n";
    }
    return 0;
}