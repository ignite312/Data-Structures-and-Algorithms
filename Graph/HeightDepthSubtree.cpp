#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
vector<int> G[N], depth(N), height(N), subtree(N);
bool vis[N];

void dfs(int parent) {
    vis[parent] = true;
    for(auto child : G[parent]) {
        if(vis[child])continue;
        depth[child] = depth[parent] + 1;
        dfs(child);
        subtree[parent] = subtree[parent] + subtree[child] + 1;
        height[parent] = max(height[parent], height[child] + 1);
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
        dfs(1);
        for (int i = 1; i <= n; ++i)
            cout << depth[i] << " " << height[i] << " " << subtree[i] << "\n";
    }
    return 0;
}
